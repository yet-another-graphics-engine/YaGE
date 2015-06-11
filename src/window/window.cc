#include "../yage.h"
#include "../draw/canvas.h"
#include "window.h"
#include "../util/encoding.h"
#ifdef _WIN32
#ifdef _MSC_VER
#define _X86_
#endif
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#endif // _WIN32

using namespace yage::util;

namespace yage {
namespace window {

gpointer user_thread(gpointer *param) {
  auto func = reinterpret_cast<int (*)(int, char**)>(param[0]);
  auto &ret = *reinterpret_cast<int *>(param[1]);

  ret = func(argc, argv);
  gtk_main_quit();
  return nullptr;
}

bool Window::quit_all_windows_destroyed = true;

int Window::init(int (*new_main)()) {
  msg_queue_ = g_async_queue_new();
  gtk_init(nullptr, nullptr);

  #ifdef _WIN32
  GtkSettings* settings = gtk_settings_get_default();
  gtk_settings_set_string_property(settings, "gtk-font-name", "Microsoft YaHei 10", "Sans 10");
  //gtk_settings_set_string_property(settings, "gtk-icon-theme-name", "flattr", "gnome-light");
  gtk_settings_set_long_property(settings, "gtk-xft-antialias", 1, nullptr);
  gtk_settings_set_string_property(settings, "gtk-xft-rgba", "rgb", "none");
  #endif // _WIN32

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

void Window::set_max_size(Window* this_, int &width, int &height)
{
  #ifdef _WIN32
  if(width == -1)
    width = GetSystemMetrics(SM_CXFULLSCREEN);
  if(height == -1)
    height = GetSystemMetrics(SM_CYFULLSCREEN);
  #else
  /*int title_bar_height = 0;
  if(this_->init_flag_)
  {
    GdkWindow* X_window = gtk_widget_get_window(this_->gtk_draw_);
    GdkRectangle rect;
    gdk_window_get_frame_extents(X_window, &rect);
    title_bar_height = rect.height - gdk_window_get_height(X_window);
    g_print("titlebar_height=%d\n",title_bar_height);
  }*/
  GdkScreen* screen = gtk_window_get_screen(this_->gtk_window_);
  int mirror = gdk_screen_get_primary_monitor(screen);
  GdkRectangle area;
  gdk_screen_get_monitor_workarea(screen,mirror,&area);
  if(width == -1)
    width = area.width;
  if(height == -1)
    height = area.height - this_->title_bar_height_;
  #endif // _WIN32
}

/*
 * Functions do real GUI work.
 * These function are all executed in GUI thread.
 * These function should return false, to signal GTK that the source should be
 * removed.
 */
void Window::exec_create(Window *this_, int &width, int &height) {
  this_->cairo_surface_ = nullptr;

  GtkWindow *&gtk_window_ = this_->gtk_window_;
  gtk_window_ = GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL));
  gtk_window_set_position(gtk_window_, GTK_WIN_POS_CENTER);
  gtk_window_set_resizable(gtk_window_, false);
  this_->init_flag_ = false;
  this_->title_bar_height_ = 0;

  if(width == -1 || height == -1)
    set_max_size(this_, width, height);
  else
  {
    if (width <= 0)
      width = 100;
    if (height <= 0)
      height = 100;
  }
  this_->window_width_ = this_->window_min_width_ = width;
  this_->window_height_ = this_->window_min_height_ = height;
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

  //gtk_widget_set_size_request(gtk_draw_, width, height);
  gtk_widget_set_size_request(GTK_WIDGET(gtk_window_), width, height);

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
}

void Window::exec_show(Window *this_) {
  gtk_widget_show_all(GTK_WIDGET(this_->gtk_window_));
}

void Window::exec_redraw(GtkWidget *gtk_draw) {
  gtk_widget_queue_draw(gtk_draw);
}

void Window::exec_hide(Window *this_) {
  gtk_widget_hide(GTK_WIDGET(this_->gtk_window_));
}

void Window::exec_destroy(Window *this_) {
  if (this_->gtk_window_) {
    gtk_widget_destroy(GTK_WIDGET(this_->gtk_window_));
    this_->gtk_window_ = nullptr;
    this_->gtk_draw_ = nullptr;
  }
}

void Window::exec_set_title(Window *this_, char *title) {
  gtk_window_set_title(this_->gtk_window_, title);
}

void Window::exec_set_resizable(Window *this_, bool &resizable) {
  GdkGeometry geo;
  if(gtk_window_get_resizable(this_->gtk_window_) == FALSE && resizable)
  {
    gtk_window_set_resizable(this_->gtk_window_, resizable);
    geo.min_width = this_->window_min_width_;
    geo.min_height = this_->window_min_height_;
    gtk_window_set_geometry_hints(this_->gtk_window_, nullptr, &geo,
                                  GDK_HINT_MIN_SIZE);
  }
  else if(gtk_window_get_resizable(this_->gtk_window_) && resizable == false)
  {
    geo.min_width = this_->window_width_;
    geo.min_height = this_->window_height_;
    gtk_window_set_geometry_hints(this_->gtk_window_, nullptr, &geo,
                                  GDK_HINT_MIN_SIZE);
    gtk_window_set_resizable(this_->gtk_window_, resizable);
  }
}

void Window::exec_get_resizable(Window *this_, bool &resizable) {
  if(this_->gtk_window_)
    resizable = gtk_window_get_resizable(this_->gtk_window_) ? true : false;
  else
    resizable = false;
}

void Window::exec_set_size(Window *this_, int &width, int &height) {
  if(width == -1 || height == -1)
    set_max_size(this_, width, height);

  if(width < this_->window_min_width_ && height < this_->window_min_height_)
    return;
  if(width == this_->window_width_ && height == this_->window_height_)
    return;

  this_->window_width_ = width;
  this_->window_height_ = height;
  this_->size_change_flag_ = false;
  if (gtk_window_get_resizable(this_->gtk_window_)) {
    gtk_window_resize(this_->gtk_window_, width, height);
  } else {
    GdkGeometry geo;
    geo.min_width = width;
    geo.min_height = height;
    gtk_window_set_geometry_hints(this_->gtk_window_, nullptr, &geo,
                                  GDK_HINT_MIN_SIZE);
  }
}

void Window::exec_get_size(Window *this_, int &width, int &height) {
  gtk_window_get_size(this_->gtk_window_, &width, &height);
}

/*
 * Proxy functions
 * Request to execute worker functions in GUI thread and wait for the return.
 */
Window::Window(int width, int height) {
  runner_call(exec_create, this, &width, &height);
}

void Window::show() {
  runner_call(exec_show, this);
  while(!init_flag_)
    g_usleep(100);
}

void Window::hide() {
  runner_call(exec_hide, this);
}

void Window::destroy() {
  runner_call(exec_destroy, this);
}

void Window::set_title(const std::string &title) {
  std::string utf_8_title = yage::util::convert_string(title);
  runner_call(exec_set_title, this, const_cast<char *>(utf_8_title.c_str()));
}

void Window::set_resizable(bool resizable) {
  runner_call(exec_set_resizable, this, &resizable);
}

bool Window::is_resizable() {
  bool result;
  runner_call(exec_get_resizable, this, &result);
  return result;
}

void Window::set_size(int width, int height) {
  size_change_flag_ = true;
  runner_call(exec_set_size, this, &width, &height);
  while(size_change_flag_ == false);
}

void Window::get_size(int &width, int &height) {
  width = this->window_width_;
  height = this->window_height_;
}

GtkWindow *Window::pro_get_gtk_window() {
  return gtk_window_;
}

GtkWidget *Window::pro_get_gtk_draw() {
  return gtk_draw_;
}

void Window::set_canvas(Canvas &canvas) {
  // Maintain Cairo's internal reference counter:
  // Decrease the previous counter when window exits or binds to a new surface
  // Increase the counter of the new surface
  if (cairo_surface_ != nullptr)
    cairo_surface_destroy(cairo_surface_);
  cairo_surface_ = canvas.pro_get_cairo_surface();
  cairo_surface_reference(cairo_surface_);
}

void Window::update() {
  runner_call_ex(exec_redraw, false, GTK_WIDGET(this->gtk_draw_));
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

}  // namespace window
}  // namespace yage

