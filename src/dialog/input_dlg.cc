#include "input_dlg.h"
#include "../yage.h"

namespace yage {
namespace dialog {

InputDlg::InputDlg(const char *title)
{
  yage::core::gtk_runner.call(exec_create,
      {this, const_cast<char *>(title), nullptr});
}

InputDlg::InputDlg(const char *title, Window &window)
{
  yage::core::gtk_runner.call(exec_create,
      {this, const_cast<char *>(title), window.pro_get_gtk_window()});
}

InputDlg::~InputDlg()
{
  yage::core::gtk_runner.call(exec_destroy, {this});
}

gboolean InputDlg::exec_destroy(gpointer *param)
{
  auto this_ = reinterpret_cast<InputDlg *>(param[0]);

  if (this_->gtk_dialog_) gtk_widget_destroy(GTK_WIDGET(this_->gtk_dialog_));

  yage::core::gtk_runner.signal();
  return false;
}

gboolean InputDlg::exec_set_message(gpointer *param)
{
  auto this_ = reinterpret_cast<InputDlg *>(param[0]);
  auto text = reinterpret_cast<const char *>(param[1]);

  gtk_label_set_markup(this_->gtk_label_, text);

  yage::core::gtk_runner.signal();
  return false;
}

gboolean InputDlg::msg_entry_on_key(GtkWidget *widget, GdkEvent *event, InputDlg *source)
{
  if (event->key.hardware_keycode == 36 ||
      event->key.hardware_keycode == 76) {
    // Enter pressed
    gtk_dialog_response(source->gtk_dialog_, GTK_RESPONSE_OK);
    return true;
  }
  return false;
}

gboolean InputDlg::exec_create(gpointer *param)
{
  auto this_ = reinterpret_cast<InputDlg *>(param[0]);
  auto title = reinterpret_cast<const char *>(param[1]);
  auto parent = reinterpret_cast<GtkWindow *>(param[2]);

  this_->gtk_dialog_ = GTK_DIALOG(gtk_dialog_new_with_buttons(
      title, parent, GTK_DIALOG_MODAL,
      "_OK", GTK_RESPONSE_OK,
      "_Cancel", GTK_RESPONSE_CANCEL,
      nullptr));

  gtk_dialog_set_default_response(this_->gtk_dialog_, GTK_RESPONSE_OK);

  this_->gtk_entry_ = GTK_ENTRY(gtk_entry_new());
  this_->gtk_label_ = GTK_LABEL(gtk_label_new(nullptr));

  g_signal_connect(this_->gtk_entry_, "key-press-event",
                   G_CALLBACK(msg_entry_on_key), this_);

  GtkContainer *container =
      GTK_CONTAINER(gtk_dialog_get_content_area(this_->gtk_dialog_));

  gtk_container_set_border_width(container, 10);
  gtk_container_add(container, GTK_WIDGET(this_->gtk_label_));
  gtk_container_add(container, GTK_WIDGET(this_->gtk_entry_));
  gtk_widget_show_all(GTK_WIDGET(container));

  yage::core::gtk_runner.signal();
  return false;
}

gboolean InputDlg::exec_show(gpointer *param)
{
  auto this_ = reinterpret_cast<InputDlg *>(param[0]);
  auto &yage_str = *reinterpret_cast<std::string *>(param[1]);
  auto &ret = *reinterpret_cast<gint *>(param[2]);

  gint run_ret = gtk_dialog_run(GTK_DIALOG(this_->gtk_dialog_));
  if (run_ret == GTK_RESPONSE_OK) {
    const char *gtk_str = gtk_entry_get_text(this_->gtk_entry_);
    yage_str = gtk_str;
    ret = true;
  } else {
    ret = false;
  }

  yage::core::gtk_runner.signal();
  return false;
}

bool InputDlg::show(std::string &str)
{
  bool ret;
  gtk_runner.call(exec_show, {this, &str, &ret});
  return ret;
}

void InputDlg::set_message(const char *text) {
  gtk_runner.call(exec_set_message, {this, const_cast<char *>(text)});
}


}  // namespace dialog
}  // namespace yage
