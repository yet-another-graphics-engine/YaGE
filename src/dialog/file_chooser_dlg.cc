#include "file_chooser_dlg.h"
#include "../yage.h"

namespace yage {
namespace dialog {
FileChooserDlg::FileChooserDlg(action_type action, const char *title)
{
  yage::core::gtk_runner.call(exec_create,
      {this, &action, const_cast<char *>(title), nullptr});
}

FileChooserDlg::FileChooserDlg(action_type action, const char *title, Window &window)
{
  yage::core::gtk_runner.call(exec_create,
      {this, &action, const_cast<char *>(title), window.pro_get_gtk_window()});
}

FileChooserDlg::~FileChooserDlg()
{
  yage::core::gtk_runner.call(exec_destroy, {this});
}

gboolean FileChooserDlg::exec_destroy(gpointer *param)
{
  auto this_ = reinterpret_cast<FileChooserDlg *>(param[0]);

  if (this_->gtk_dialog_) gtk_widget_destroy(GTK_WIDGET(this_->gtk_dialog_));

  yage::core::gtk_runner.signal();
  return false;
}

gboolean FileChooserDlg::exec_create(gpointer *param)
{
  auto this_ = reinterpret_cast<FileChooserDlg *>(param[0]);
  auto action = *reinterpret_cast<action_type *>(param[1]);
  auto title = reinterpret_cast<const char *>(param[2]);
  auto parent = reinterpret_cast<GtkWindow *>(param[3]);

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

  yage::core::gtk_runner.signal();
  return false;
}

gboolean FileChooserDlg::exec_show(gpointer *param)
{
  auto this_ = reinterpret_cast<FileChooserDlg *>(param[0]);
  auto &std_str = *reinterpret_cast<std::string *>(param[1]);
  auto &ret = *reinterpret_cast<gint *>(param[2]);

  char *c_str = nullptr;
  ret = false;

  gint run_ret = gtk_dialog_run(GTK_DIALOG(this_->gtk_dialog_));
  if (run_ret == GTK_RESPONSE_ACCEPT) {
    c_str = gtk_file_chooser_get_filename(this_->gtk_dialog_);
  }

  if (c_str) {
    std_str = c_str;
    g_free(c_str);
    ret = true;
  }

  yage::core::gtk_runner.signal();
  return false;
}

bool FileChooserDlg::show(std::string &str) {
  bool ret;
  gtk_runner.call(exec_show, {this, &str, &ret});
  return ret;
}

}  // namespace dialog
}  // namespace yage
