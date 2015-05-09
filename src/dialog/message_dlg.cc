#include "../yage.h"
#include "message_dlg.h"

namespace yage {
namespace dialog {

gboolean MessageDlg::exec_create(gpointer *param)
{
  auto this_ = reinterpret_cast<MessageDlg *>(param[0]);
  auto &button = *reinterpret_cast<button_type *>(param[1]);
  auto &icon = *reinterpret_cast<icon_type *>(param[2]);
  auto *parent = reinterpret_cast<GtkWindow *>(param[3]);

  GtkButtonsType btn_type;
  switch (button) {
    case button_type_ok:
      btn_type = GTK_BUTTONS_OK;
      break;
    case button_type_yes_no:
      btn_type = GTK_BUTTONS_YES_NO;
      break;
    case button_type_ok_cancel:
      btn_type = GTK_BUTTONS_OK_CANCEL;
      break;
    case button_type_close:
      btn_type = GTK_BUTTONS_CLOSE;
      break;
    case button_type_cancel:
      btn_type = GTK_BUTTONS_CANCEL;
      break;
    case button_type_none:
    default:
      btn_type = GTK_BUTTONS_NONE;
      break;
  }

  GtkMessageType msg_type;
  switch (icon) {
    case icon_type_info:
      msg_type = GTK_MESSAGE_INFO;
      break;
    case icon_type_warning:
      msg_type = GTK_MESSAGE_WARNING;
      break;
    case icon_type_question:
      msg_type = GTK_MESSAGE_QUESTION;
      break;
    case icon_type_error:
      msg_type = GTK_MESSAGE_ERROR;
      break;
    case icon_type_none:
    default:
      msg_type = GTK_MESSAGE_OTHER;
  }

  this_->gtk_dialog_ = gtk_message_dialog_new(
      parent, GTK_DIALOG_MODAL, msg_type, btn_type, nullptr);

  yage::core::gtk_runner.signal();
  return false;
}

gboolean MessageDlg::exec_set_title(gpointer *param)
{
  auto this_ = reinterpret_cast<MessageDlg *>(param[0]);
  auto title = reinterpret_cast<char *>(param[1]);

  gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(this_->gtk_dialog_), title);

  yage::core::gtk_runner.signal();
  return false;
}

gboolean MessageDlg::exec_set_message(gpointer *param)
{
  auto this_ = reinterpret_cast<MessageDlg *>(param[0]);
  auto msg = reinterpret_cast<char *>(param[1]);

  gtk_message_dialog_format_secondary_markup(
      GTK_MESSAGE_DIALOG(this_->gtk_dialog_), "%s", msg);

  yage::core::gtk_runner.signal();
  return false;
}

gboolean MessageDlg::exec_show(gpointer *param)
{
  auto this_ = reinterpret_cast<MessageDlg *>(param[0]);
  auto &ret = *reinterpret_cast<gint *>(param[1]);
  gint run_ret = gtk_dialog_run(GTK_DIALOG(this_->gtk_dialog_));

  switch(run_ret) {
    case GTK_RESPONSE_REJECT:
      ret = result_type_reject;
      break;
    case GTK_RESPONSE_ACCEPT:
      ret = result_type_accept;
      break;
    case GTK_RESPONSE_OK:
      ret = result_type_ok;
      break;
    case GTK_RESPONSE_CANCEL:
      ret = result_type_cancel;
      break;
    case GTK_RESPONSE_CLOSE:
      ret = result_type_close;
      break;
    case GTK_RESPONSE_YES:
      ret = result_type_yes;
      break;
    case GTK_RESPONSE_NO:
      ret = result_type_no;
      break;
    case GTK_RESPONSE_APPLY:
      ret = result_type_apply;
      break;
    case GTK_RESPONSE_HELP:
      ret = result_type_help;
      break;
    case GTK_RESPONSE_DELETE_EVENT:
    case GTK_RESPONSE_NONE:
    default:
      ret = result_type_none;
      break;
  };

  yage::core::gtk_runner.signal();
  return false;
}

gboolean MessageDlg::exec_destroy(gpointer *param)
{
  auto this_ = reinterpret_cast<MessageDlg *>(param[0]);

  if (this_->gtk_dialog_) gtk_widget_destroy(GTK_WIDGET(this_->gtk_dialog_));

  yage::core::gtk_runner.signal();
  return false;
}

MessageDlg::MessageDlg(button_type button, icon_type icon)
{
  yage::core::gtk_runner.call(exec_create,
      {this, &button, &icon, nullptr});
}

MessageDlg::MessageDlg(button_type button, icon_type icon, Window &window)
{
  yage::core::gtk_runner.call(exec_create,
      {this, &button, &icon, window.pro_get_gtk_window()});
}

MessageDlg::~MessageDlg()
{
  yage::core::gtk_runner.call(exec_destroy, {this});
}

void MessageDlg::set_title(const char *title) {
  gtk_runner.call(exec_set_title, {this, const_cast<char *>(title)});
}

void MessageDlg::set_message(const char *message) {
  gtk_runner.call(exec_set_message, {this, const_cast<char *>(message)});
}

MessageDlg::result_type MessageDlg::show() {
  result_type ret;
  gtk_runner.call(exec_show, {this, &ret});
  return ret;
}

}  // namespace dialog
}  // namespace yage
