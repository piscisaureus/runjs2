
CFLAGS	=-Wall -Wextra -pedantic -Ideps/faio
LDFLAGS	= -lrt

BUILDTYPE ?= Release

ifeq ($(BUILDTYPE),Release)
	CFLAGS += -Os
	LDFLAGS += -s
else
	CFLAGS += -O0 -g
endif

B = out/$(BUILDTYPE)

.PHONY: all clean

all: $(B)/rund

clean:
	@rm -fr out/

$(B)/rund: packet.c main.c ioutil.c process.c server.c spawn.c util.c
	@mkdir -p $(B)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
