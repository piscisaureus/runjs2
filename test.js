
var net = require('net');


function write_uint(conn, val) {
  var buf = new Buffer(4);
  buf.writeUInt32LE(val, 0);
  return conn.write(buf);
}


function write_string(conn, s) {
  var buf, len;

  s = s + "";
  
  len = Buffer.byteLength(s);
  buf = new Buffer(len + 4);
  
  buf.writeUInt32LE(len, 0);
  buf.write(s, 4, len);
  
  conn.write(buf);
}


function write_string_list(conn, list) {
  return write_string(conn, list.join('\0') + '\0');
}


function send_start_cmd(conn) {

  write_uint(conn, 1); // START
  write_string(conn, "test"); // tag
  write_string(conn, "echo"); // file
  write_string_list(conn, ["echo", "hoi"]); // args
  write_string_list(conn, Object.keys(process.env).map(function(key) { 
    return key + '=' + process.env[key]; 
  })); // env

  for (var i = 0; i < 3; i++)
    write_string(conn, "argument");
    
  conn.pipe(process.stdout);
  conn.on('end', function() { console.log('end') });
  conn.on('close', function() { console.log('close') });
}


var conn = net.createConnection('/tmp/runjs.sock');

send_start_cmd(conn);


