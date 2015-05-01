#ifndef WINDOW_H_YDVLBPKF
#define WINDOW_H_YDVLBPKF
#include <gtk/gtk.h>
#include "app.h"

namespace yage {
namespace core {

class Window {
	friend class App;
private:
	GtkWidget *gtk_;

public:
	Window();
	~Window();
	void show();
	bool is_valid();
};

} /* core */
} /* yage */

#endif /* end of include guard: WINDOW_H_YDVLBPKF */
