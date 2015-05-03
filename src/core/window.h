#ifndef WINDOW_H_YDVLBPKF
#define WINDOW_H_YDVLBPKF
#include <gtk/gtk.h>
#include "message.h"
#include "../util/runner.h"

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
  static yage::util::Runner runner_;
  static GAsyncQueue *msg_queue_;
  static size_t window_num_;

  GtkWidget *widget_draw_;
  cairo_surface_t *cairo_surface_;

  static gboolean exec_window(gpointer *param);
  static gboolean exec_show(gpointer *param);
  static gboolean exec_hide(gpointer *param);
  static gboolean exec_destroy(gpointer *param);

public:
  static void init(void (*new_main)() = nullptr);
  static bool poll(Message &msg, bool block = true);
  static void quit();

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
