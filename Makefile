CXXFLAGS=`pkg-config --cflags gtk+-3.0` -g --std=c++11 -Wall
LDFLAGS=`pkg-config --libs gtk+-3.0`
CXX=clang++

bin/test: bin/window.o bin/test.o
	$(CXX) $(LDFLAGS) bin/window.o bin/test.o -o $@

bin/window.o: src/core/window.cc src/core/window.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

bin/test.o: src/test.cc src/core/window.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	rm -rf bin/*

all: bin/test

.PHONY:
	clean all
