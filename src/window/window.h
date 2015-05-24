#ifndef WINDOW_WINDOW_H_
#define WINDOW_WINDOW_H_
#include <gtk/gtk.h>
#include "message.h"
#include "../draw/canvas.h"
#include "../util/runner.h"

namespace yage {
namespace draw {
  class Canvas;
}

namespace window {

struct Message;

class Window {
private:
  static GAsyncQueue *msg_queue_;
  static size_t window_num_;

  GtkWidget *gtk_draw_;
  GtkWindow *gtk_window_;
  cairo_surface_t *cairo_surface_;

  static void exec_create(Window *this_, int &width, int &height);
  static void exec_show(Window *this_);
  static void exec_hide(Window *this_);
  static void exec_redraw(GtkWidget *gtk_draw);
  static void exec_destroy(Window *this_);

  static void exec_set_title(Window *this_, char *title);
  static void exec_set_resizable(Window *this_, bool &resizable);
  static void exec_set_size(Window *this_, int &width, int &height);
  static void exec_get_size(Window *this_, int &width, int &height);

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
  static int init(int (*new_main)());
  static bool poll(Message &msg, bool block = true);
  static void quit();

  Window(int width = 640, int height = 480);

  ~Window();
  void show();
  void hide();
  void destroy();
  bool is_valid();
  void set_title(const gchar *title);
  void set_resizable(bool resizable);
  void set_size(int width, int height);
  void get_size(int &width, int &height);

  GtkWidget *pro_get_gtk_draw();
  GtkWindow *pro_get_gtk_window();

  void set_canvas(Canvas &canvas);
  void update();
};

} /* window */
} /* yage */

#endif /* end of include guard: WINDOW_H_YDVLBPKF */
