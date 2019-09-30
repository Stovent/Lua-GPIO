CC = gcc
CCFLAGS = -Wall -Wextra -O3
LINKERFLAGS = -fpic -shared

LUAINC = /usr/include/lua5.1

installDir = /usr/lib
libName = libLua-GPIO.so

bin = bin
obj = $(bin)/obj
objs = $(obj)/lua-gpio.o $(obj)/pins.o

.PHONY: clean
.PHONY: dir
.PHONY: install

libLua-gpio: dir
	$(CC) $(CCFLAGS) -I$(LUAINC) -c src/lua-gpio.c -o $(obj)/lua-gpio.o
	$(CC) $(CCFLAGS) -I$(LUAINC) -c src/pins.c -o $(obj)/pins.o
	$(CC) $(LINKERFLAGS) -llua5.1 $(objs) -o $(bin)/$(libName)

dir:
	mkdir -p bin
	mkdir -p bin/obj

clean:
	rm $(obj)/lua-gpio.o
	rm $(obj)/pins.o
	rm $(bin)/$(libName)

install:
	cp $(bin)/$(libName) $(installDir)/$(libName)
