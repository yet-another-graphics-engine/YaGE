#include <algorithm>
#include "animation.h"

namespace yage {
namespace draw {
using namespace yage::window;

gboolean Animation::timeout_func(CallParam &param) {
  gtk_widget_queue_draw_region(param.widget, param.region);
  cairo_region_destroy(param.region);
  delete &param;
  return FALSE;
}

void Animation::setup_timeout(Window &window) {
  // Update frames expected_delay_time <= current_delay * kGreedyRate
  static const double kGreedyRate = 1.2;
  // max fps = 30
  static const int kMinDelay = 33;

  List &list = window.anim_list_;

  // Get the most urgent update request
  int delay = INT_MAX;
  for (List::iterator i = list.begin(); i != list.end(); ++i) {
    Animation &anim = **i;

    int cur_delay = gdk_pixbuf_animation_iter_get_delay_time(anim.iter_);
    delay = std::min(delay, cur_delay);
  }
  if (delay < kMinDelay) delay = kMinDelay;

  // Get the expected update region
  int threshold_delay = static_cast<int>(delay * kGreedyRate);
  cairo_region_t *region = cairo_region_create();
  for (List::iterator i = list.begin(); i != list.end(); ++i) {
    Animation &anim = **i;
    int cur_delay = gdk_pixbuf_animation_iter_get_delay_time(anim.iter_);
    if (cur_delay > threshold_delay) continue;

    cairo_rectangle_int_t rect;
    rect.x      = static_cast<int>(anim.x_),
    rect.y      = static_cast<int>(anim.y_),
    rect.width  = anim.width_;
    rect.height = anim.height_;
    cairo_region_union_rectangle(region, &rect);
    anim.should_update = true;
  }

  // Register callback on timeout
  CallParam *param = new CallParam;
  param->widget = window.pro_get_gtk_draw();
  param->region = region;

  gdk_threads_add_timeout(delay,
                          reinterpret_cast<GSourceFunc>(timeout_func),
                          param);
}

void Animation::on_draw(Window &window, cairo_t *cairo) {
  List &list = window.anim_list_;
  for (List::iterator i = list.begin(); i != list.end(); ++i) {
    Animation &anim = **i;
    // FIXME Temporarily force redraw everything, because users may redraw any
    // time thus overwriting the animated region.
    //if (!anim.should_update) continue;

    anim.should_update = false;
    gdk_pixbuf_animation_iter_advance(anim.iter_, NULL);
    GdkPixbuf *buf = gdk_pixbuf_animation_iter_get_pixbuf(anim.iter_);
    gdk_cairo_set_source_pixbuf(cairo, buf, anim.x_, anim.y_);
    cairo_paint(cairo);
  }

  setup_timeout(window);
}

Animation::Animation(yage::window::Window &window, double x, double y,
                     const std::string &path) :
  window_(window), iter_(NULL), height_(-1), width_(-1), x_(x), y_(y) {

  buf_ = gdk_pixbuf_animation_new_from_file(path.c_str(), NULL);
  if (gdk_pixbuf_animation_is_static_image(buf_)) {
    g_object_unref(buf_);
    buf_ = NULL;
    return;
  }

  width_ = gdk_pixbuf_animation_get_width(buf_);
  height_ = gdk_pixbuf_animation_get_height(buf_);
  iter_ = gdk_pixbuf_animation_get_iter(buf_, NULL);

  List &list = window.anim_list_;
  list.push_back(this);
  setup_timeout(window);
}

Animation::~Animation() {
  window_.anim_list_.remove(this);
  window_.update();
  g_object_unref(iter_);
  g_object_unref(buf_);
}

}  // namespace draw
}  // namespace yage


