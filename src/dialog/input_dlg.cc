#include "input_dlg.h"
#include "../main.h"
#include "../util/encoding.h"

namespace yage {
namespace dialog {

gboolean InputDlg::msg_entry_on_enter_key(GtkWidget *widget, InputDlg *source)
{
  gtk_dialog_response(source->gtk_dialog_, GTK_RESPONSE_OK);
  return true;
}

gboolean InputDlg::msg_button_ok_on_click(GtkWidget *widget,InputDlg* source)
{
  gtk_dialog_response(source->gtk_dialog_, GTK_RESPONSE_OK);
  return true;
}

gboolean InputDlg::msg_button_cancel_on_click(GtkWidget *widget,InputDlg *source)
{
  gtk_dialog_response(source->gtk_dialog_, GTK_RESPONSE_CANCEL);
  return true;
}

void InputDlg::msg_entry_on_icon_press(GtkEntry* entry,GtkEntryIconPosition icon_pos,
                                        GdkEvent *event)
{
  gtk_entry_set_text(entry,"");
}

void InputDlg::exec_destroy(InputDlg *this_)
{
  if (this_->gtk_dialog_) {
    gtk_widget_destroy(GTK_WIDGET(this_->gtk_dialog_));
    this_->gtk_dialog_ = NULL;
  }
}

void InputDlg::exec_set_message(InputDlg *this_, const std::string &text)
{
  gtk_label_set_markup(this_->gtk_label_, text.c_str());
}

void InputDlg::exec_create(InputDlg *this_,
                           const char *title,
                           GtkWindow *parent)
{
  this_->gtk_dialog_ = GTK_DIALOG(gtk_dialog_new());
  gtk_window_set_title(GTK_WINDOW(this_->gtk_dialog_), title);
  gtk_window_set_icon_name(GTK_WINDOW(this_->gtk_dialog_),"gtk-edit");
  gtk_window_set_position(GTK_WINDOW(this_->gtk_dialog_),GTK_WIN_POS_CENTER);
  gtk_dialog_set_default_response(this_->gtk_dialog_, GTK_RESPONSE_OK);
  gtk_window_set_transient_for(GTK_WINDOW(this_->gtk_dialog_), parent);

  GtkBox* dialog_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 0));
  GtkBox* label_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0));
  GtkBox* entry_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0));
  GtkBox* button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10));
  gtk_box_pack_start(dialog_box, GTK_WIDGET(label_box), TRUE, TRUE, 5);
  gtk_box_pack_start(dialog_box, GTK_WIDGET(entry_box), TRUE, TRUE, 5);
  gtk_box_pack_start(dialog_box, gtk_separator_new(GTK_ORIENTATION_HORIZONTAL), FALSE, FALSE, 5);
  gtk_box_pack_start(dialog_box, GTK_WIDGET(button_box), FALSE, FALSE, 5);

  this_->gtk_label_ = GTK_LABEL(gtk_label_new(NULL));
  gtk_label_set_line_wrap(this_->gtk_label_, TRUE);

  this_->gtk_entry_ = GTK_ENTRY(gtk_entry_new());
  gtk_entry_set_icon_activatable(this_->gtk_entry_, GTK_ENTRY_ICON_SECONDARY, TRUE);
  #ifdef _WIN32
  gtk_entry_set_icon_from_stock(this_->gtk_entry_, GTK_ENTRY_ICON_SECONDARY, GTK_STOCK_CLEAR);
  #else
  gtk_entry_set_icon_from_icon_name(this_->gtk_entry_, GTK_ENTRY_ICON_SECONDARY, "edit-clear");
  #endif // _WIN32
  g_signal_connect(this_->gtk_entry_, "activate",
                   G_CALLBACK(msg_entry_on_enter_key), this_);
  g_signal_connect(this_->gtk_entry_, "icon-press",G_CALLBACK(msg_entry_on_icon_press),NULL);

  #ifdef _WIN32
  GtkButton* button_ok = GTK_BUTTON(gtk_button_new_from_stock(GTK_STOCK_OK));
  #else
  GtkButton* button_ok = GTK_BUTTON(gtk_button_new_with_label("OK"));
  gtk_button_set_image(button_ok, gtk_image_new_from_icon_name("gtk-ok", GTK_ICON_SIZE_SMALL_TOOLBAR));
  #endif // _WIN32
  gtk_widget_set_size_request(GTK_WIDGET(button_ok),100,1);
  g_signal_connect(GTK_WIDGET(button_ok), "clicked",
                   G_CALLBACK(msg_button_ok_on_click), this_);

  #ifdef _WIN32
  GtkButton* button_cancel = GTK_BUTTON(gtk_button_new_from_stock(GTK_STOCK_CANCEL));
  #else
  GtkButton* button_cancel = GTK_BUTTON(gtk_button_new_with_label("Cancel"));
  gtk_button_set_image(button_cancel, gtk_image_new_from_icon_name("gtk-cancel", GTK_ICON_SIZE_SMALL_TOOLBAR));
  #endif // _WIN32
  gtk_widget_set_size_request(GTK_WIDGET(button_cancel),100,1);
  g_signal_connect(GTK_WIDGET(button_cancel), "clicked",
                   G_CALLBACK(msg_button_cancel_on_click), this_);

  gtk_box_pack_start(label_box, GTK_WIDGET(this_->gtk_label_), FALSE, FALSE, 0);
  gtk_box_pack_start(entry_box, GTK_WIDGET(this_->gtk_entry_), TRUE, TRUE, 0);
  gtk_box_pack_end(button_box, GTK_WIDGET(button_cancel), FALSE, FALSE, 0);
  gtk_box_pack_end(button_box, GTK_WIDGET(button_ok), FALSE, FALSE, 0);

  GtkContainer *container =
      GTK_CONTAINER(gtk_dialog_get_content_area(this_->gtk_dialog_));
  gtk_container_set_border_width(container, 10);
  gtk_container_add(container, GTK_WIDGET(dialog_box));
  gtk_widget_show_all(GTK_WIDGET(container));
}

void InputDlg::exec_show(InputDlg *this_, std::string &yage_str, bool &ret)
{
  gtk_window_resize(GTK_WINDOW(this_->gtk_dialog_),500,1);
  gint run_ret = gtk_dialog_run(GTK_DIALOG(this_->gtk_dialog_));
  if (run_ret == GTK_RESPONSE_OK) {
    const char *gtk_str = gtk_entry_get_text(this_->gtk_entry_);
    yage_str = gtk_str;
    ret = true;
  } else {
    ret = false;
  }
}

bool InputDlg::show(std::string &str)
{
  bool ret;
  runner_call(exec_show, this, &str, &ret);
  return ret;
}

void InputDlg::set_message(const std::string &text)
{
  //std::string utf_8_text = yage::util::convert_string(text);
  runner_call(exec_set_message, this, const_cast<std::string*>(&text));
}

InputDlg::InputDlg(const std::string &title)
{
  //std::string utf_8_title = yage::util::convert_string(title);
  runner_call(exec_create, this, const_cast<char *>(title.c_str()), NULL);
}

InputDlg::InputDlg(const std::string &title, yage::window::Window &window)
{
  //std::string utf_8_title = yage::util::convert_string(title);
  runner_call(exec_create, this, const_cast<char *>(title.c_str()),
              window.pro_get_gtk_window());
}

InputDlg::~InputDlg()
{
  runner_call(exec_destroy, this);
}

}  // namespace dialog
}  // namespace yage
