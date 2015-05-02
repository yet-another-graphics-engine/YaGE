#include "core/window.h"
using namespace yage::core;

int main(int argc, char *argv[])
{
	Window::init();
	Window window;
	window.show();
	gtk_main();
	return 0;
}
