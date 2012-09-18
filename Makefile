
CFLAGS	=-Wall -Wextra
LDFLAGS	=

BUILDTYPE ?= Release

ifeq ($(BUILDTYPE),Release)
	CFLAGS += -Os
	LDFLAGS += -s
else
	CFLAGS += -O0 -g
endif

B = out/$(BUILDTYPE)

.PHONY: all clean

all: $(B)/runjs-agent

clean:
	@rm -fr out/

$(B)/runjs-agent: cmd.c main.c proc.c spawn.c
	@mkdir -p $(B)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
