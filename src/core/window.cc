#include <glib.h>
#include "window.h"

namespace yage {
namespace core {

gpointer gui_thread(gpointer data) {
  gtk_init(NULL, NULL);
  gtk_main();
  return nullptr;
}

gpointer main_thread(gpointer data) {
  reinterpret_cast<gpointer (*)()>(data)();
  gtk_main_quit();
  return nullptr;
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
  this_->cairo_surface_ = nullptr;
  using namespace yage::core::message_handler;

  GtkWidget *&widget_window_ = this_->widget_window_;
  widget_window_ = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  //gtk_window_set_resizable(GTK_WINDOW(widget_window_), false);
  gtk_window_set_default_size(GTK_WINDOW(widget_window_), 640, 480);

  gtk_widget_set_events(widget_window_, gtk_widget_get_events(widget_window_)
      | GDK_FOCUS_CHANGE | GDK_KEY_PRESS | GDK_KEY_RELEASE);

  g_signal_connect(widget_window_,
                  "destroy", G_CALLBACK(window_on_destroy), this_);
  g_signal_connect(widget_window_,
                  "focus-in-event",       G_CALLBACK(window_on_focus), this_);
  g_signal_connect(widget_window_,
                  "focus-out-event",      G_CALLBACK(window_on_focus), this_);
  g_signal_connect(widget_window_,
                  "key-press-event",      G_CALLBACK(window_on_key), this_);
  g_signal_connect(widget_window_,
                  "key-release-event",    G_CALLBACK(window_on_key), this_);

  GtkWidget *&widget_draw_ = this_->widget_draw_;
  widget_draw_ = gtk_drawing_area_new();
  gtk_widget_add_events(widget_draw_, GDK_BUTTON_PRESS_MASK |
                                      GDK_BUTTON_RELEASE_MASK |
                                      GDK_POINTER_MOTION_MASK);

  g_signal_connect(widget_draw_,
                  "button-press-event",   G_CALLBACK(draw_on_button), this_);
  g_signal_connect(widget_draw_,
                  "button-release-event", G_CALLBACK(draw_on_button), this_);
  g_signal_connect(widget_draw_,
                  "motion-notify-event",  G_CALLBACK(draw_on_motion), this_);
  g_signal_connect(widget_draw_,
                  "configure-event",      G_CALLBACK(draw_on_conf), this_);
  g_signal_connect(widget_draw_,
                  "draw",                 G_CALLBACK(draw_on_draw), this_);

  gtk_container_add(GTK_CONTAINER(widget_window_), widget_draw_);

  ++Window::window_num_;
  fprintf(stderr, "New window=%p widget=%p\n", this_, widget_draw_);

  runner_.signal();
  return false;
}

gboolean Window::exec_show(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);

  gtk_widget_show_all(this_->widget_window_);

  runner_.signal();
  return false;
}

gboolean Window::exec_hide(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);

  gtk_widget_hide(this_->widget_window_);

  runner_.signal();
  return false;
}

gboolean Window::exec_destroy(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);

  if (this_->widget_window_)
    gtk_widget_destroy(this_->widget_window_);

  runner_.signal();
  return false;
}

gboolean Window::exec_set_title(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);
  const gchar *title = reinterpret_cast<const gchar *>(param[1]);

  gtk_window_set_title(GTK_WINDOW(this_->widget_window_), title);

  runner_.signal();
  return false;
}

gboolean Window::exec_set_resizable(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);
  bool resizable = *reinterpret_cast<const bool *>(param[1]);

  gtk_window_set_resizable(GTK_WINDOW(this_->widget_window_), resizable);

  runner_.signal();
  return false;
}

gboolean Window::exec_set_size(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);
  int width = *reinterpret_cast<const int *>(param[1]);
  int height = *reinterpret_cast<const int *>(param[2]);

  gtk_window_resize(GTK_WINDOW(this_->widget_window_), width, height);

  runner_.signal();
  return false;
}

gboolean Window::exec_get_size(gpointer *param)
{
  Window *this_ = reinterpret_cast<Window *>(param[0]);
  int &width = *reinterpret_cast<int *>(param[1]);
  int &height = *reinterpret_cast<int *>(param[2]);

  gtk_window_get_size(GTK_WINDOW(this_->widget_window_), &width, &height);

  runner_.signal();
  return false;
}

void Window::init(void (*new_main)(void)){
  msg_queue_ = g_async_queue_new();
  if (new_main) {
    g_thread_new("YaGE main", main_thread, reinterpret_cast<gpointer>(new_main));
    gui_thread(nullptr);
  } else {
    g_thread_new("YaGE event", gui_thread, nullptr);
  }
}

Window::Window() {
  runner_.call(exec_window, {this});
}

void Window::show() {
  runner_.call(exec_show, {this});
}

void Window::hide() {
  runner_.call(exec_hide, {this});
}

void Window::destroy() {
  runner_.call(exec_destroy, {this});
}

void Window::set_title(const gchar *title) {
  runner_.call(exec_set_title, {this,
      reinterpret_cast<gpointer>(const_cast<gchar *>(title))});
}

void Window::set_resizable(bool resizable) {
  runner_.call(exec_set_resizable, {this,
      reinterpret_cast<gpointer>(&resizable)});
}

void Window::set_size(int width, int height) {
  runner_.call(exec_set_size, {this,
      reinterpret_cast<gpointer>(&width),
      reinterpret_cast<gpointer>(&height)});
}

void Window::get_size(int &width, int &height) {
  runner_.call(exec_get_size, {this,
      reinterpret_cast<gpointer>(&width),
      reinterpret_cast<gpointer>(&height)});
}

void Window::quit() {
  gtk_main_quit();
}

Window::~Window() {
  destroy();
}

bool Window::is_valid() {
  return widget_draw_ != nullptr && widget_window_ != nullptr;
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

