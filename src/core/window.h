#ifndef WINDOW_H_YDVLBPKF
#define WINDOW_H_YDVLBPKF
#include <gtk/gtk.h>
#include "message.h"

void test_draw(); // only for test; will be removed after drawing framework's finish

namespace yage {
namespace core {

class Window;

struct Message;

class Window {
  friend void yage::core::message_handler::push_queue(Message &msg);
  friend void yage::core::message_handler::window_on_destroy(GtkWidget *widget, Window *source);
  friend gboolean yage::core::message_handler::draw_on_conf(GtkWidget *widget, GdkEventConfigure *event, Window *source);
  friend gboolean yage::core::message_handler::draw_on_draw(GtkWidget *widget, cairo_t *cairo, Window *source);
  friend void ::test_draw();

  private:
  static GAsyncQueue *msg_queue_;
  static size_t window_num_;

  GtkWidget *widget_draw_;
  cairo_surface_t *cairo_surface_;

  public:
  static void init();
  static bool poll(Message &msg, bool block = true);

  Window();
  ~Window();
  void show();
  void hide();
  void destroy();
  bool is_valid();
};

} /* core */
} /* yage */

#endif /* end of include guard: WINDOW_H_YDVLBPKF */
