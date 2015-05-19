#ifndef TEST_TEST_H_
#define TEST_TEST_H_
#include "../yage.h"
#include "../window/window.h"

#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace yage::window;
using namespace std;

void sleep_sec(int seconds);

#endif /* end of include guard: TEST_TEST_H_ */
