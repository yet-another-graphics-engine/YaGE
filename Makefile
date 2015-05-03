CXXFLAGS=`pkg-config --cflags gtk+-3.0 glib-2.0` -g --std=c++11 -Wall -DUSE_X11
LDFLAGS=`pkg-config --libs gtk+-3.0` -lX11
CXX=clang++
OBJS=bin/window.o bin/message.o bin/runner.o bin/test.o

bin/test: $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

bin/window.o: src/core/window.cc src/core/window.h src/core/message.h src/util/runner.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

bin/message.o: src/core/message.cc src/core/message.h src/core/window.h 
	$(CXX) $(CXXFLAGS) $< -o $@ -c

bin/test.o: src/test.cc src/core/window.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

bin/runner.o: src/util/runner.cc src/util/runner.h
	$(CXX) $(CXXFLAGS) $< -o $@ -c

clean:
	rm -rf bin/*

all: bin/test

.PHONY:
	clean all
