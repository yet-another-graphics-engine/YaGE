#ifndef DRAW_ANIMATION_H_
#define DRAW_ANIMATION_H_
#include <string>
#include <list>
#include <gtk/gtk.h>
#include "../window/window.h"

namespace yage {
namespace draw {

class Animation {
private:
  typedef yage::window::Window::AnimationList List;
  struct CallParam {
    GtkWidget *widget;
    cairo_region_t *region;
  };

  yage::window::Window &window_;
  GdkPixbufAnimation *buf_;
  GdkPixbufAnimationIter *iter_;

  bool should_update;
  int height_, width_;
  double x_, y_;

  static gboolean timeout_func(CallParam &param);
  static void setup_timeout(yage::window::Window &window);

public:
  Animation(yage::window::Window &window, double x, double y,
            const std::string &path);

  ~Animation();

  static void on_draw(yage::window::Window &window, cairo_t *cairo);
};

}  // namespace draw
}  // namespace yage

#endif  // #ifndef DRAW_ANIMATION_H_
