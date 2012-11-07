

var assert = require('assert');


/* Node 0.6 compatibility */
if (!Buffer.concat) {
  Buffer.concat = function(list, length) {
    if (!Array.isArray(list)) {
      throw new Error('Usage: Buffer.concat(list, [length])');
    }
  
    if (list.length === 0) {
      return new Buffer(0);
    } else if (list.length === 1) {
      return list[0];
    }
  
    if (typeof length !== 'number') {
      length = 0;
      for (var i = 0; i < list.length; i++) {
        var buf = list[i];
        length += buf.length;
      }
    }
  
    var buffer = new Buffer(length);
    var pos = 0;
    for (var i = 0; i < list.length; i++) {
      var buf = list[i];
      buf.copy(buffer, pos);
      pos += buf.length;
    }
    return buffer;
  };
}
/* End that */

var packetTypes = [];

function definePacketType(layout) {
  function Constructor(values) {
    if (!values)
      return;
    for (var key in values) {
      if (values.hasOwnProperty(key))
        this[key] = values[key];
    }
  }
  
  Constructor.prototype._type = packetTypes.length;
  Constructor.prototype._layout = layout;

  packetTypes.push(Constructor);
  
  return Constructor;
}

var StartPacket = definePacketType([
  { type: 'string', name: 'tag'} ,
  { type: 'string', name: 'file' },
  { type: 'string_list', name: 'argv' },
  { type: 'string_list', name: 'envv' },
  { type: 'string', name: 'cwd' }
]);

var StopPacket = definePacketType([
  { type: 'string', name: 'tag' }
]);

var StartSuccessPacket = definePacketType([
  { type: 'number', name: 'pid' }
]);

var ErrorPacket = definePacketType([
  { type: 'number', name: 'err' },
  { type: 'string', name: 'message' },
  { type: 'string', name: 'syscall' }
]);


function encodePacket(packet) {
  var i, j, size, field, value, buffer, pos, len, layout;
  
  layout = packet._layout;
  
  // Compute the required size
  size = 0;

  for (i = 0; i < layout.length; i++) {
    field = layout[i];
    value = packet[field.name];
    
    switch (field.type) {
      case 'number':
        assert(typeof value === 'number' &&
               value === Math.floor(value));
        size += 4;
        break;
        
      case 'string':
        assert(typeof value === 'string');
        size += 4; // String length
        size += Buffer.byteLength(value); // String contents
        break;
        
      case 'string_list':
        assert(value instanceof Array);
    
        size += 4; // Array length;

        for (j = 0; j < value.length; j++) {
          assert(typeof value[j] === 'string');
          size += 4;  // String length
          size += Buffer.byteLength(value[j]);
        }    
        break;
        
      default:
        assert(0);
    }
  }

  buffer = new Buffer(size + 4 + 4); // Extra bytes are for the header
  pos = 0;

  // Write header
  buffer.writeUInt32LE(packet._type, pos);
  pos += 4;
  buffer.writeUInt32LE(size, pos);
  pos += 4;
    
  for (i = 0; i < layout.length; i++) {
    field = layout[i];
    value = packet[field.name];
    
    switch (field.type) {
      case 'number':
        buffer.writeInt32LE(value, pos);
        pos += 4;
        break;
        
      case 'string':
        len = buffer.write(value, pos + 4);
        buffer.writeInt32LE(len, pos);
        pos += 4 + len;
        break;
        
      case 'string_list':
        buffer.writeInt32LE(value.length, pos);
        pos += 4;
        
        for (j = 0; j < value.length; j++) {
          len = buffer.write(value[j], pos + 4);
          buffer.writeInt32LE(len, pos);
          pos += 4 + len;
        }        
        break;
    }
  }
  
  return buffer;
}


function decodePacket(buffer) {
  var type, size, packet, layout, i, j, field, value, pos, len, count;
  
  pos = 0;
  
	if (buffer.length < (4 + 4))
	  return null;
  
  type = buffer.readInt32LE(pos);
  pos += 4;
  size = buffer.readInt32LE(pos);
  pos += 4;
  
  if (buffer.length < (4 + 4 + size))
  	return null;
  
  packet = new packetTypes[type]();
  
  layout = packet._layout;
  assert(type === packet._type);

  for (i = 0; i < layout.length; i++) {
    field = layout[i];
    
    switch (field.type) {
      case 'number':
        value = buffer.readInt32LE(pos);
        pos += 4;
        break;
        
      case 'string':
        len = buffer.readInt32LE(pos);
        pos += 4;
        value = buffer.slice(pos, pos + len).toString();
        pos += len;
        break;
        
      case 'string_list':
        count = buffer.readInt32LE(pos);
        pos += 4;
        
        value = new Array(count);
        
        for (j = 0; j < count; j++) {
          len = buffer.readInt32LE(pos);
          pos += 4;
          value[j] = buffer.slice(pos, pos + len).toString();
          pos += len;
        }
        break;
        
      default:
        assert(0);
    }
    
    packet[field.name] = value;
  }
  
  return { packet: packet,
  				 left: buffer.slice(pos) };
}


function getEnvv() {
  var envv = [];
  for (var key in process.env) {
    envv.push(key + '=' + process.env[key]);
  }
  return envv;
}


var p = new StartPacket({
  tag: 'test',
  file: 'echo',
  cwd: '.',
  argv: ['echo', 'eat this mofo'],
  envv: getEnvv()
});

console.log(p);

var buf = encodePacket(p);

console.log(buf);
console.log(buf.toString());


console.log("writing");



var conn = require('net').createConnection("/tmp/runjs.sock");
streamPackets(conn);
conn.write(buf);
conn.on('packet', console.log);

var left = new Buffer(0);

function streamPackets(stream) {
  stream.on('data', function(buffer) {
    console.log(buffer);
    var result;

    left = Buffer.concat([left, buffer]);
      
    while ((result = decodePacket(left))) {
      left = result.left;
      stream.emit('packet', result.packet);
    }
  });
}
