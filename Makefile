CC = gcc
CCFLAGS = -Wall -Wextra -fPIC -O3
LINKERFLAGS = -shared

LUAINC = /usr/include/lua5.1

installDir = /usr/lib
libName = libLua-GPIO.so

bin = bin
obj = $(bin)/obj
objs = $(obj)/lua-gpio.o $(obj)/pins.o

.PHONY: clean
.PHONY: dir
.PHONY: install

$(libName): dir
	$(CC) $(CCFLAGS) -I$(LUAINC) -c src/lua-gpio.c -o $(obj)/lua-gpio.o
	$(CC) $(CCFLAGS) -I$(LUAINC) -c src/pins.c -o $(obj)/pins.o
	$(CC) $(LINKERFLAGS) $(objs) -o $(bin)/$@

dir:
	mkdir -p $(obj)

clean:
	rm $(obj)/lua-gpio.o
	rm $(obj)/pins.o
	rm $(bin)/$(libName)

install:
	cp $(bin)/$(libName) $(installDir)/$(libName)
