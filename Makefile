CXXFLAGS=`pkg-config --cflags gtk+-3.0 glib-2.0` -g --std=c++11 -Wall -DUSE_X11
LDFLAGS=`pkg-config --libs gtk+-3.0` -lX11
CXX=clang++

bin/test: bin/window.o bin/unix.o bin/test.o
	$(CXX) $(LDFLAGS) bin/window.o bin/unix.o bin/test.o -o $@

bin/window.o: src/core/window.cc src/core/window.h src/platform/unix.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

bin/test.o: src/test.cc src/core/window.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

bin/unix.o: src/platform/unix.cc src/platform/unix.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	rm -rf bin/*

all: bin/test

.PHONY:
	clean all
