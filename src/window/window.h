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

  /**
   * @brief Excutes the given function in an additional user thread.
   * The function will be called automatically to excute the code in the function "int main()"
   * when the program starts.
   * @param new_main The given function.
   * @return Returns the value which the function new_main returns;
   * @attention DO NOT call it manually.
   */
  static int init(int (*new_main)());

  /**
   * @brief Gets a message from pool.
   *
   * @param block: If no message availiable, whether block until new message comes.
   * @param [out] msg: The arrived message will be written here
   * @return Returns false when there are no window left, thus no messages can be
   *  generated. Returns true when new message can arrive in the future.
   */
  static bool poll(Message &msg, bool block = true);

  /**
   * @brief Closes the window and exit the program.
   */
  static void quit();

  /**
   * @brief Creates a new window.
   * @param start_width The initial width of the window.The default value is 640.
   * @param start_height The initial height of the window.The default value is 480.
   * @note The new window is not resizable by default.And the start_width and the start_height are also
   *       the min width and the min height of the new window.
   * @attention The new window don't be set any canvas by default.If you want to display something on the
   * window,you must call the function Window::set_canvas to set a new canvas for the window.
   */
  Window(int width = 640, int height = 480);

  ~Window();

  /**
   * @brief Shows the window on screen.
   */
  void show();

  /**
   * @brief Hides the window.
   * @attention The window after being hidden will not appear in the task bar.
   */
  void hide();

  /**
   * @brief Destroys the window.
   * @attention The window after being destroyed is not valid any more.
   */
  void destroy();

  /**
   * @brief Checks if the window is valid.
   * @return Returns false if the window was destroyed.Otherwise return true.
   */
  bool is_valid();

  /**
   * @brief Sets a new title for the window.
   * @param title The string used as the new title.
   */
  void set_title(const gchar *title);

  /**
   * @brief Sets whether the user can resize the window.
   * @param resizable true if the user can resize the window.
   * @attention If the resizable is true,you should handle the resizing event
   * when the window is resized.The window will push a resizing massage to the message queue when it is resized,
   * and you can use the function Window::poll to get a Message which contains
   * the resizing info,and then handle the resizing events.
   * @see Window::poll
   * @see Message
   */
  void set_resizable(bool resizable);

  /**
   * @brief Sets a new size for the window.
   * @param width The new width for the window.
   * @param height The new height for the window.
   * @attention The window's size will be changed really only if the window is resizable
   * and both the new width and the new height are not smaller than the min width and the
   * min height of the window.The window will push a resizing Message to the massage queue
   * when its size is changed,and you should handle the resizing event.
   * @see Window::set_resizable;
   * @see Window::Window;
   * @see Window::poll;
   * @see Message
  **/
  void set_size(int width, int height);

  /**
   * @brief Gets the current size of the window.
   * @param [out]width The current width of the window will be written here.
   * @param [out]height The current height of the window will be written here.
   */
  void get_size(int &width, int &height);

  /**
   * @brief Sets a new canvas for the window to update its interface.
   * @param canvas The new canvas set for the window.If it's NULL,all the content of
   * the window will be cleared by white color the next time when the window updates.
   */
  void set_canvas(Canvas &canvas);

  /**
   * @brief Lets the window updates its interface.
   * @note If the window didn't be set any canvas,
  void update();

  GtkWidget *pro_get_gtk_draw();
  GtkWindow *pro_get_gtk_window();
};

} /* window */
} /* yage */

#endif /* end of include guard: WINDOW_H_YDVLBPKF */
