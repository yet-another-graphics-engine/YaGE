#ifndef WINDOW_WINDOW_H_
#define WINDOW_WINDOW_H_
#include <string>
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

/**
 * @brief yage::window::Window is the most important part of GUI in a YaGE program.
 *
 * The window can display graphics and be used for user interaction.Each window object consists of a GTK window,
 * and a GTK drawing area,and all the window objects share a message queue.When a mouse event,a keyboard or a window event
 * happens to a window object,it will push a relative message to the shared message queue.You can implement the user interaction
 * by getting messages from the message queue and handle them.
 * The graphics which the window displays comes from a canvas.If you want to display graphics on the window,
 * you should set a canvas for the window.
 *
 * @see yage::window::Message
 * @see yage::draw::Canvas
 */
class Window {
private:
  static GAsyncQueue *msg_queue_;
  static size_t window_num_;

  GtkWidget *gtk_draw_;
  GtkWindow *gtk_window_;
  cairo_surface_t *cairo_surface_;

  /*Not allow to copy the window object*/
  Window(const Window& window){}
  /*The following functions are working in the GUI thread*/
  static void exec_create(Window *this_, int &width, int &height);
  static void exec_show(Window *this_);
  static void exec_hide(Window *this_);
  static void exec_redraw(GtkWidget *gtk_draw);
  static void exec_destroy(Window *this_);
  static void exec_set_title(Window *this_, char *title);
  static void exec_set_resizable(Window *this_, bool &resizable);
  static void exec_get_resizable(Window *this_, bool &resizable);
  static void exec_set_size(Window *this_, int &width, int &height);
  static void exec_get_size(Window *this_, int &width, int &height);

  static void msg_push_queue(Message &msg);

  /*the following functions are callback function for mouse events,key events and window events*/
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
   * @brief The flag that whether the program exits automatically when all the window
   * Objects are destroyed.The default value is true.
   */
  static bool quit_all_windows_destroyed;

  /**
   * @brief Executes the given function in an additional user thread.
   * @note The function will be called automatically to execute the code in the function "int main()"
   * when the program starts.
   * @param new_main The given function.
   * @return Returns the value which the function new_main returns.
   * @attention DO NOT call it manually.
   */
  static int init(int (*new_main)());

  /**
   * @brief Gets a message from pool.
   *
   * @param block: If no message available, whether block until new message comes.
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
   * @param start_width The initial width of the window.The default value is 640.If the value is -1,
   * the width will be the "main desktop" work area's width(maybe it equals to the entire screen width).
   * @param start_height The initial height of the window.The default value is 480.If the value is -1,
   * the height will be the "main desktop" work area's height(maybe it equals to the entire screen height).
   * @note The new window is not resizable by default.And the start_width and the start_height are also
   *       the min width and the min height of the new window.
   * @attention The new window doesn't bind any canvas by default.If you want to display graphics on the
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
   * @note The window will be destroyed automatically when it is closed by the user.
   * @note The window will push a destroying message to the message queue after being destroyed.
   * @attention The window after being destroyed is not valid any more.
   * @see Message
   */
  void destroy();

  /**
   * @brief Checks if the window is valid.
   * @return Returns false if the window was destroyed.
   */
  bool is_valid();

  /**
   * @brief Sets a new title for the window.
   * @param title The string used as the new title.
   */
  void set_title(const std::string &title);

  /**
   * @brief Sets whether the user can resize the window.
   * @param resizable True if the user can resize the window.
   * @attention If the resizable is true,you should handle the resizing event
   * when the window is resized.The window will push a resizing massage to the message queue when it is resized,
   * and you can use the function Window::poll to get a Message which contains
   * the resizing info,and then handle the resizing events.
   * @see Window::poll
   * @see yage::window::Message
   */
  void set_resizable(bool resizable);

  /**
   * @brief Gets if the window is resizable
   * @return Returns true if the window is resizable.
   */
  bool is_resizable();

  /**
   * @brief Sets a new size for the window.
   * @param width The new width for the window.If the value is -1,
   * the width will be the "main desktop" work area's width(maybe it equals to the entire screen width).
   * @param height The new height for the window.If the value is -1,
   * the height will be the "main desktop" work area's height(maybe it equals to the entire screen height).
   * @attention The window's size won't be changed really if both the new width and the new height
   * are smaller than the min width and the min height of the window or both of them
   * are equal to the current width and the current height of the window.
   * The window will push a resizing Message to the massage queue
   * when its size is changed really,and you should handle the resizing event.
   * @see Window::set_resizable
   * @see Window::Window
   * @see Window::poll
   * @see yage::window::Message
   */
  void set_size(int width, int height);

  /**
   * @brief Gets the current size of the window.
   * @param [out]width The current width value of the window will be written here.
   * @param [out]height The current height value of the window will be written here.
   */
  void get_size(int &width, int &height);

  /**
   * @brief Sets a new canvas for the window to update its interface.
   * @param canvas The new canvas set for the window.If it's NULL,
   * the window will be filled by white color the next time when the window updates.
   */
  void set_canvas(Canvas &canvas);

  /**
   * @brief Lets the window use the canvas which it binds to update its interface.
   * @note If the window doesn't bind any canvas,it will be filled by white color.
   * @attention The process of the interface updating is asynchronous.
   */
  void update();

  /**
   * @brief (Pro)Gets the pointer of the GTK drawing area included in the window.
   * @return Returns the pointer of the GTK drawing area.Returns NULL if the window
   * is invalid.
   */
  GtkWidget *pro_get_gtk_draw();

  /**
   * @brief (Pro)Gets the pointer of the GTK window included in the window.
   * @return Returns the pointer of the GTK window.Returns NULL if the window is invalid.
   */
  GtkWindow *pro_get_gtk_window();
};

} /* window */
} /* yage */

#endif /* end of include guard: WINDOW_H_YDVLBPKF */
