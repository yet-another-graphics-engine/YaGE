CC=gcc
CFLAGS=-std=gnu99 -O2
LDFLAGS=-s -shared -Wl,--subsystem,windows -static-libgcc

path.dll : path.o pluginapi.o
	$(CC) -o path.dll path.o pluginapi.o $(LDFLAGS)

path.o : path.c
	$(CC) -c path.c -o path.o $(CFLAGS)

pluginapi.o : pluginapi.c
	$(CC) -c pluginapi.c -o pluginapi.o $(CFLAGS)

.PHONY: clean
clean :
	rm -f path.dll
	rm -f *.o
