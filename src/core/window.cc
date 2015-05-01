#include "window.h"

namespace yage {
namespace core {

Window::Window()
{
	 gtk_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	 gtk_widget_set_events (gtk_, gtk_widget_get_events(gtk_)
			 | GDK_BUTTON_PRESS_MASK
			 | GDK_POINTER_MOTION_MASK);
	 App::window_add(gtk_, this);
}

Window::~Window()
{
	gtk_widget_destroy(gtk_);
}

void Window::show()
{
	gtk_widget_show_all(gtk_);
}

bool Window::is_valid()
{
	return gtk_;
}

} /* core */
} /* yage */

