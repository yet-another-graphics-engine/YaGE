#include "window.h"

namespace yage {
namespace core {

Window::Window()
{
	 gtk = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	 gtk_widget_set_events (gtk, gtk_widget_get_events(gtk)
			 | GDK_BUTTON_PRESS_MASK
			 | GDK_POINTER_MOTION_MASK);
	 App::window_add(gtk, this);
}

Window::~Window()
{
	 App::window_del(gtk, this);
}

void Window::show() const
{
	gtk_widget_show_all(gtk);
}

} /* core */
} /* yage */

