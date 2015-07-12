#include "../main.h"
#include "../../include/yage.h"
#include "../window/window.h"

using namespace yage;

struct yage_window {
  window::Window *window;
  draw::Canvas *canvas;
  draw::Canvas *canvas_bg;
  draw::Canvas *canvas_btn;
};

namespace yage {
namespace api {
namespace yage {

  const draw::Color kTransparentColor(0, 0, 0, 0);
  const size_t kMaxTextBuffer = 2048;
  extern yage_window *g_window;
  extern bool g_auto_update;

  inline struct yage_canvas *get_canvas_ext(draw::Canvas *canvas = g_window->canvas) {
    return reinterpret_cast<yage_canvas *>(canvas);
  }

  inline draw::Canvas *get_canvas_int(yage_canvas *ext) {
    return reinterpret_cast<draw::Canvas *>(ext);
  }

  void force_update(yage_window *window = g_window);

  inline void update(yage_window *window = g_window) {
    if (g_auto_update) force_update(window);
  }

}  // namespace yage
}  // namespace api
}  // namespace yage

