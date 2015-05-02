#include <X11/Xlib.h>

namespace yage {
namespace platform {

void enable_x11_thread_support()
{
	XInitThreads();
}

} /* core */
} /* yage */

