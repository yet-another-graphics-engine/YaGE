#include "core/window.h"
#include <cstdlib>
using namespace yage::core;

int main(int argc, char *argv[])
{
	Window::init();
	Window window;
	window.show();
	system("sleep 2");
	return 0;
}
