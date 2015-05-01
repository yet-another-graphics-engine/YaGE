#ifndef WINDOW_H_YDVLBPKF
#define WINDOW_H_YDVLBPKF
#include <gtk/gtk.h>
#include "app.h"

namespace yage {
namespace core {

class Window {
private:
	GtkWidget *gtk;

public:
	Window();
	~Window();
	void show() const;
};

} /* core */
} /* yage */

#endif /* end of include guard: WINDOW_H_YDVLBPKF */
