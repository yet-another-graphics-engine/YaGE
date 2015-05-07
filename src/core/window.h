#ifndef WINDOW_H_YDVLBPKF
#define WINDOW_H_YDVLBPKF
#include <gtk/gtk.h>
#include "message.h"
#include "../util/runner.h"
//#include "../draw/canvas.h"


void test_draw(); // only for test; will be removed after drawing framework's finish

namespace yage {
namespace draw {
  class Canvas;
}
namespace core {

class Window {
  friend void ::test_draw();

private:
  static yage::util::Runner runner_;
  static GAsyncQueue *msg_queue_;
  static size_t window_num_;

  GtkWidget *gtk_draw_;
  GtkWindow *gtk_window_;
  yage::draw::Canvas *canvas_;

  static gboolean exec_window(gpointer *param);
  static gboolean exec_show(gpointer *param);
  static gboolean exec_hide(gpointer *param);
  static gboolean exec_destroy(gpointer *param);
  static gboolean exec_set_title(gpointer *param);
  static gboolean exec_set_resizable(gpointer *param);
  static gboolean exec_set_size(gpointer *param);
  static gboolean exec_get_size(gpointer *param);
  static gboolean exec_redraw(gpointer *param);

  static void msg_push_queue(Message &msg);

  static void msg_window_on_destroy(    GtkWidget *widget,
                                        Window *source);

  static gboolean msg_window_on_focus(  GtkWidget *widget,
                                        GdkEvent *event,
                                        Window *source);

  static gboolean msg_window_on_key(    GtkWidget *widget,
                                        GdkEvent *event,
                                        Window *source);

  static gboolean msg_draw_on_button(   GtkWidget *widget,
                                        GdkEvent *event,
                                        Window *source);

  static gboolean msg_draw_on_motion(   GtkWidget *widget,
                                        GdkEvent *event,
                                        Window *source);

  static gboolean msg_draw_on_conf(     GtkWidget *widget,
                                        GdkEventConfigure *event,
                                        Window *source);

  static gboolean msg_draw_on_draw(     GtkWidget *widget,
                                        cairo_t *cairo,
                                        Window *source);

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
  void set_title(const gchar *title);
  void set_resizable(bool resizable);
  void set_size(int width, int height);
  void get_size(int &width, int &height);
  void pro_redraw();
  yage::draw::Canvas &pro_get_canvas(void);
  GtkWidget *pro_get_gtk_draw(void);
};

} /* core */
} /* yage */

#endif /* end of include guard: WINDOW_H_YDVLBPKF */
