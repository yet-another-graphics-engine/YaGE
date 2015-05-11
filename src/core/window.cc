#include <glib.h>
#include "../yage.h"
#include "window.h"
#include "../draw/canvas.h"

namespace yage {
namespace core {

gpointer user_thread(gpointer *param) {
  auto func = reinterpret_cast<int (*)()>(param[0]);
  auto &ret = *reinterpret_cast<int *>(param[1]);

  ret = func();
  gtk_main_quit();
  return nullptr;
}

int Window::init(int (*new_main)()) {

  msg_queue_ = g_async_queue_new();
  gtk_init(nullptr, nullptr);

  int ret = 0;
  gpointer param[] = {reinterpret_cast<gpointer>(new_main), &ret};
  g_thread_new("YaGE user", reinterpret_cast<GThreadFunc>(user_thread), param);
  gtk_main();

  // user_thread() will set the value of ret
  return ret;
}

/*
 * Static variables.
 */
GAsyncQueue *Window::msg_queue_ = nullptr;

size_t Window::window_num_ = 0;

yage::util::Runner Window::runner_;

/*
 * Functions do real GUI work.
 * These function are all executed in GUI thread.
 * These function should return false, to signal GTK that the source should be
 * removed.
 */
gboolean Window::exec_window(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);
  this_->canvas_ = nullptr;

  GtkWindow *&gtk_window_ = this_->gtk_window_;
  gtk_window_ = reinterpret_cast<GtkWindow*>(gtk_window_new(GTK_WINDOW_TOPLEVEL));

  // Default: not resizable
  GdkGeometry geo;
  geo.min_width = 640;
  geo.min_height = 480;
  gtk_window_set_geometry_hints(this_->gtk_window_, nullptr, &geo,
                                GDK_HINT_MIN_SIZE);
  gtk_window_set_resizable(gtk_window_, false);

  // Setup signals for main window
  gtk_widget_add_events(GTK_WIDGET(gtk_window_),
                        GDK_FOCUS_CHANGE | GDK_KEY_PRESS | GDK_KEY_RELEASE);
  g_signal_connect(gtk_window_, "destroy",
                   G_CALLBACK(msg_window_on_destroy), this_);
  g_signal_connect(gtk_window_, "focus-in-event",
                   G_CALLBACK(msg_window_on_focus), this_);
  g_signal_connect(gtk_window_, "focus-out-event",
                   G_CALLBACK(msg_window_on_focus), this_);
  g_signal_connect(gtk_window_, "key-press-event",
                   G_CALLBACK(msg_window_on_key), this_);
  g_signal_connect(gtk_window_, "key-release-event",
                   G_CALLBACK(msg_window_on_key), this_);

  // Setup drawing_area
  GtkWidget *&gtk_draw_ = this_->gtk_draw_;
  gtk_draw_ = gtk_drawing_area_new();
  gtk_widget_add_events(gtk_draw_, GDK_BUTTON_PRESS_MASK |
                                   GDK_BUTTON_RELEASE_MASK |
                                   GDK_POINTER_MOTION_MASK);
  g_signal_connect(gtk_draw_, "button-press-event",
                   G_CALLBACK(msg_draw_on_button), this_);
  g_signal_connect(gtk_draw_, "button-release-event",
                   G_CALLBACK(msg_draw_on_button), this_);
  g_signal_connect(gtk_draw_, "motion-notify-event",
                   G_CALLBACK(msg_draw_on_motion), this_);
  g_signal_connect(gtk_draw_, "configure-event",
                   G_CALLBACK(msg_draw_on_conf), this_);
  g_signal_connect(gtk_draw_, "draw",
                   G_CALLBACK(msg_draw_on_draw), this_);
  gtk_container_add(GTK_CONTAINER(gtk_window_), gtk_draw_);

  // Add window counter
  ++Window::window_num_;
  fprintf(stderr, "New window=%p widget=%p\n", this_, gtk_draw_);

  gtk_runner.signal();
  return false;
}

gboolean Window::exec_show(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);

  gtk_widget_show_all(GTK_WIDGET(this_->gtk_window_));

  gtk_runner.signal();
  return false;
}

gboolean Window::exec_redraw(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);

  gtk_widget_queue_draw(GTK_WIDGET(this_->gtk_draw_));

  runner_.signal();
  return false;
}

gboolean Window::exec_hide(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);

  gtk_widget_hide(GTK_WIDGET(this_->gtk_window_));

  gtk_runner.signal();
  return false;
}

gboolean Window::exec_destroy(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);

  if (this_->gtk_window_)
    gtk_widget_destroy(GTK_WIDGET(this_->gtk_window_));

  gtk_runner.signal();
  return false;
}

gboolean Window::exec_set_title(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);
  const gchar *title = reinterpret_cast<const gchar *>(param[1]);

  gtk_window_set_title(this_->gtk_window_, title);

  gtk_runner.signal();
  return false;
}

gboolean Window::exec_set_resizable(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);
  bool resizable = *reinterpret_cast<const bool *>(param[1]);

  gtk_window_set_resizable(this_->gtk_window_, resizable);

  if (resizable) {
    GdkGeometry geo;
    geo.min_width = 1;
    geo.min_height = 1;
    gtk_window_set_geometry_hints(this_->gtk_window_, nullptr, &geo,
                                  GDK_HINT_MIN_SIZE);
  }

  gtk_runner.signal();
  return false;
}

gboolean Window::exec_set_size(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);
  int width = *reinterpret_cast<const int *>(param[1]);
  int height = *reinterpret_cast<const int *>(param[2]);

  gtk_window_resize(this_->gtk_window_, width, height);
  if (gtk_window_get_resizable(this_->gtk_window_)) {
    gtk_window_resize(this_->gtk_window_, width, height);
  } else {
    GdkGeometry geo;
    geo.min_width = width;
    geo.min_height = height;
    gtk_window_set_geometry_hints(this_->gtk_window_, nullptr, &geo,
                                  GDK_HINT_MIN_SIZE);
  }

  gtk_runner.signal();
  return false;
}

gboolean Window::exec_get_size(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);
  int &width = *reinterpret_cast<int *>(param[1]);
  int &height = *reinterpret_cast<int *>(param[2]);

  gtk_window_get_size(this_->gtk_window_, &width, &height);

  gtk_runner.signal();
  return false;
}


/*
 * Proxy functions
 * Request to execute worker functions in GUI thread and wait for the return.
 */
Window::Window() {
  gtk_runner.call(exec_window, {this});
}

void Window::show() {
  gtk_runner.call(exec_show, {this});
}

void Window::hide() {
  gtk_runner.call(exec_hide, {this});
}

void Window::destroy() {
  gtk_runner.call(exec_destroy, {this});
}

void Window::set_title(const gchar *title) {
  gtk_runner.call(exec_set_title, {this,
               reinterpret_cast<gpointer>(const_cast<gchar *>(title))});
}

void Window::set_resizable(bool resizable) {
  gtk_runner.call(exec_set_resizable, {this,
               reinterpret_cast<gpointer>(&resizable)});
}

void Window::set_size(int width, int height) {
  gtk_runner.call(exec_set_size, {this,
               reinterpret_cast<gpointer>(&width),
               reinterpret_cast<gpointer>(&height)});
}

void Window::get_size(int &width, int &height) {
  gtk_runner.call(exec_get_size, {this,
               reinterpret_cast<gpointer>(&width),
               reinterpret_cast<gpointer>(&height)});
}

GtkWindow *Window::pro_get_gtk_window()
{
  return gtk_window_;
}

GtkWidget *Window::pro_get_gtk_draw()
{
  return gtk_draw_;
}

void Window::pro_redraw() {
  runner_.call(exec_redraw, {this});
}

void Window::quit() {
  gtk_main_quit();
}

Window::~Window() {
  destroy();
}

bool Window::is_valid() {
  return gtk_draw_ != nullptr && gtk_window_ != nullptr;
}

/**
 * Get a message from pool.
 *
 * @param block: If no message availiable, whether block until new message comes.
 * @param [out] msg: The arrived message will be written here
 * @return Returns false when there are no window left, thus no messages can be
 *  generated. Returns true when new message can arrive in the future.
 */
bool Window::poll(Message &msg, bool block) {
  if (Window::window_num_ == 0) return false;
  gpointer pmsg = block ? g_async_queue_pop(Window::msg_queue_)
                        : g_async_queue_try_pop(Window::msg_queue_);
  if (pmsg == nullptr) {
    msg.type = msg.type_nop;
  } else {
    msg = *reinterpret_cast<Message *>(pmsg);
    delete reinterpret_cast<Message *>(pmsg);
  }
  return true;
}

}  // namespace core
}  // namespace yage

