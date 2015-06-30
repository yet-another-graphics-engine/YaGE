#include "../yage.h"
#include "message_dlg.h"
#include "../util/encoding.h"

namespace yage {
namespace dialog {

void MessageDlg::exec_create(MessageDlg *this_,
                             button_type &button,
                             icon_type &icon,
                             GtkWindow *parent)
{
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
      parent, GTK_DIALOG_MODAL, msg_type, btn_type, NULL);
}

void MessageDlg::exec_set_title(MessageDlg *this_, char *title)
{
  gtk_message_dialog_set_markup(GTK_MESSAGE_DIALOG(this_->gtk_dialog_), title);
}

void MessageDlg::exec_set_message(MessageDlg *this_, char *msg)
{
  gtk_message_dialog_format_secondary_markup(
      GTK_MESSAGE_DIALOG(this_->gtk_dialog_), "%s", msg);
}

void MessageDlg::exec_show(MessageDlg *this_, int &ret)
{
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

}

void MessageDlg::exec_destroy(MessageDlg *this_)
{
  if (this_->gtk_dialog_) {
    gtk_widget_destroy(GTK_WIDGET(this_->gtk_dialog_));
    this_->gtk_dialog_ = NULL;
  }
}

MessageDlg::MessageDlg(button_type button, icon_type icon)
{
  runner_call(exec_create, this, &button, &icon, NULL);
}

MessageDlg::MessageDlg(button_type button, icon_type icon, Window &window)
{
  runner_call(exec_create, this, &button, &icon, window.pro_get_gtk_window());
}

MessageDlg::~MessageDlg()
{
  runner_call(exec_destroy, this);
}

void MessageDlg::set_title(const std::string &title) {
  std::string utf_8_title = yage::util::convert_string(title);
  runner_call(exec_set_title, this, const_cast<char *>(utf_8_title.c_str()));
}

void MessageDlg::set_message(const std::string &message) {
  std::string utf_8_title = yage::util::convert_string(message);
  runner_call(exec_set_message, this, const_cast<char *>(utf_8_title.c_str()));
}

MessageDlg::result_type MessageDlg::show() {
  result_type ret;
  runner_call(exec_show, this, &ret);
  return ret;
}

}  // namespace dialog
}  // namespace yage
