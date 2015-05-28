#include "file_chooser_dlg.h"
#include "../yage.h"
#include "../util/encoding.h"

namespace yage {
namespace dialog {
FileChooserDlg::FileChooserDlg(action_type action, const std::string &title)
{
  std::string utf_8_title = yage::util::convert_string(title);
  runner_call(exec_create, this, &action, const_cast<char *>(utf_8_title.c_str()), nullptr);
}

FileChooserDlg::FileChooserDlg(action_type action, const std::string &title, Window &window)
{
  std::string utf_8_title = yage::util::convert_string(title);
  runner_call(exec_create, this, &action, const_cast<char *>(utf_8_title.c_str()),
              window.pro_get_gtk_window());
}

FileChooserDlg::~FileChooserDlg()
{
  runner_call(exec_destroy, this);
}

void FileChooserDlg::exec_destroy(FileChooserDlg *this_)
{
  if (this_->gtk_dialog_) {
    gtk_widget_destroy(GTK_WIDGET(this_->gtk_dialog_));
    this_->gtk_dialog_ = nullptr;
  }
}

void FileChooserDlg::exec_create(FileChooserDlg *this_,
                                 action_type &action,
                                 const char *title,
                                 GtkWindow *parent)
{
  GtkFileChooserAction action_type;
  switch (action) {
    default:
    case action_type_open:
      action_type = GTK_FILE_CHOOSER_ACTION_OPEN;
      break;
    case action_type_save:
      action_type = GTK_FILE_CHOOSER_ACTION_SAVE;
      break;
    case action_type_select_folder:
      action_type = GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;
      break;
    case action_type_create_folder:
      action_type = GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER;
      break;
  }

  this_->gtk_dialog_ = GTK_FILE_CHOOSER(gtk_file_chooser_dialog_new(
      title, parent, action_type,
      "_Cancel", GTK_RESPONSE_CANCEL,
      "_Open", GTK_RESPONSE_ACCEPT,
      nullptr));

  gtk_file_chooser_set_do_overwrite_confirmation(this_->gtk_dialog_, TRUE);
}

void FileChooserDlg::exec_show(FileChooserDlg *this_,
                                   std::string &std_str,
                                   bool &ret)
{
  char *c_str = nullptr;
  ret = false;

  gint run_ret = gtk_dialog_run(GTK_DIALOG(this_->gtk_dialog_));
  if (run_ret == GTK_RESPONSE_ACCEPT) {
    c_str = gtk_file_chooser_get_filename(this_->gtk_dialog_);
  }

  if (c_str) {
    char *ansi_c_str = yage::util::utf_8_to_ansi(c_str);
    std_str = ansi_c_str;
    yage::util::free_string(ansi_c_str);
    g_free(c_str);
    ret = true;
  }
}

bool FileChooserDlg::show(std::string &str) {
  bool ret;
  runner_call(exec_show, this, &str, &ret);
  return ret;
}

}  // namespace dialog
}  // namespace yage
