#include "core/app.h"
#include "core/window.h"
using namespace yage::core;

int main(int argc, char *argv[])
{
	App app;
	Window window;
	window.show();
	gtk_main();
	return 0;
}
