CC = gcc
CCFLAGS = -Wall -Wextra -fPIC -O3 -std=gnu99
LINKERFLAGS = -shared

LUAINC = /usr/include/lua5.2

installDir = /usr/local/lib
libName = libLua-GPIO.so

bin = bin
obj = $(bin)/obj
objs = $(obj)/lua-gpio.o $(obj)/gpio.o

.PHONY: clean
.PHONY: dir
.PHONY: install
.PHONY: uninstall

$(libName): dir
	$(CC) $(CCFLAGS) -I$(LUAINC) -c src/lua-gpio.c -o $(obj)/lua-gpio.o
	$(CC) $(CCFLAGS) -I$(LUAINC) -c src/gpio.c -o $(obj)/gpio.o
	$(CC) $(LINKERFLAGS) $(objs) -o $(bin)/$@

clean:
	rm $(obj)/lua-gpio.o
	rm $(obj)/gpio.o
	rm $(bin)/$(libName)

dir:
	mkdir -p $(obj)

install:
	cp $(bin)/$(libName) $(installDir)/$(libName)

uninstall:
	rm -f $(installDir)/$(libName)
