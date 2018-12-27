CC = gcc
CCFLAGS = -fpic -shared

LUAINC = /usr/include/lua5.1

targetPath = /usr/lib
output = libLua-GPIO.so
obj = bin/obj
objs = $(obj)/lua-gpio.o $(obj)/pins.o

.PHONY: clean
.PHONY: dir

libLua-GPIO: dir
	$(CC) -o $(obj)/lua-gpio.o -I$(LUAINC) -c src/lua-gpio.c
	$(CC) -o $(obj)/pins.o -I$(LUAINC) -c src/pins.c
	$(CC) -o $(targetPath)/$(output) -llua5.1 $(CCFLAGS) $(objs)

dir:
	mkdir -p bin
	mkdir -p bin/obj

clean:
	rm $(targetPath)/$(output)
