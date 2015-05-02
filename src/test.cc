#include "core/window.h"
#include <cstdlib>
using namespace yage::core;

int main(int argc, char *argv[])
{
	Window::init();
	Window w;
	w.show();

	Message msg;
	while (Window::poll(msg)) {
		if (msg.type == msg.type_mouse
				&& msg.mouse.type == msg.mouse.type_press) {
			fprintf(stderr, "Click!\n");
			Window *w = new Window;
			w->show();
		}
	}

	return 0;
}
