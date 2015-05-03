#include "window.h"
#include <glib.h>
#include "../platform/unix.h"

namespace {

gpointer event_thread(gpointer data) {
  gtk_main();
  return nullptr;
}

}  // will be replaced soon

namespace yage {
namespace core {

GAsyncQueue *Window::msg_queue_ = nullptr;

size_t Window::window_num_ = 0;

void Window::init() {
#ifdef USE_X11
  yage::platform::enable_x11_thread_support();
#endif
  gtk_init(NULL, NULL);
  msg_queue_ = g_async_queue_new();
  g_thread_new("YaGE GTK event handler", event_thread, nullptr);
}

Window::Window() {
  using namespace yage::core::message_handler;
  cairo_surface_ = nullptr;

  GtkWidget *widget_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_events(widget_window, gtk_widget_get_events(widget_window)
      | GDK_FOCUS_CHANGE);

  g_signal_connect(widget_window,
                  "destroy", G_CALLBACK(window_on_destroy), this);
  g_signal_connect(widget_window,
                  "focus-in-event", G_CALLBACK(window_on_focus), this);
  g_signal_connect(widget_window,
                  "focus-out-event", G_CALLBACK(window_on_focus), this);

  widget_draw_ = gtk_drawing_area_new();
  gtk_widget_add_events(widget_draw_, GDK_BUTTON_PRESS_MASK |
                                      GDK_POINTER_MOTION_MASK |
                                      GDK_KEY_PRESS |
                                      GDK_KEY_RELEASE);

  g_signal_connect(widget_draw_,
                  "button-press-event",   G_CALLBACK(draw_on_button), this);
  g_signal_connect(widget_draw_,
                  "button-release-event", G_CALLBACK(draw_on_button), this);
  g_signal_connect(widget_draw_,
                  "motion-notify-event",  G_CALLBACK(draw_on_motion), this);
  g_signal_connect(widget_draw_,
                  "key-press-event",      G_CALLBACK(draw_on_key), this);
  g_signal_connect(widget_draw_,
                  "key-release-event",    G_CALLBACK(draw_on_key), this);
  g_signal_connect(widget_draw_,
                  "configure-event",      G_CALLBACK(draw_on_conf), this);
  g_signal_connect(widget_draw_,
                  "draw",                 G_CALLBACK(draw_on_draw), this);

  gtk_container_add(GTK_CONTAINER(widget_window), widget_draw_);

  ++Window::window_num_;
  fprintf(stderr, "New window=%p widget=%p\n", this, this->widget_draw_);
}

Window::~Window() {
  destroy();
}

void Window::show() {
  gtk_widget_show_all(gtk_widget_get_toplevel(widget_draw_));
}

void Window::hide() {
  gtk_widget_hide(gtk_widget_get_toplevel(widget_draw_));
}

void Window::destroy() {
  if (widget_draw_) gtk_widget_destroy(gtk_widget_get_toplevel(widget_draw_));
}

bool Window::is_valid() {
  return widget_draw_ != nullptr;
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

