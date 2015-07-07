#include "../main.h"
#include "../../include/yage.h"
#include "../window/window.h"

using namespace yage;
namespace yage {
namespace api {
namespace yage {

  const draw::Color kTransparentColor(0, 0, 0, 0);
  const size_t kMaxTextBuffer = 2048;

  extern window::Window *g_window;
  extern draw::Canvas *g_canvas_bg;
  extern draw::Canvas *g_canvas;
  extern draw::Canvas *g_canvas_btn;
  extern draw::Paint *g_paint;
  extern draw::Color g_fill_color;
  extern draw::Color g_border_color;

    void update();
}  // namespace yage
}  // namespace api
}  // namespace yage

