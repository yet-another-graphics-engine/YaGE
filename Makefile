bin/test: src/test.cpp
	g++ `pkg-config --cflags gtk+-3.0` --std=c++11 -Wall -g `pkg-config --libs gtk+-3.0` $< -o $@
