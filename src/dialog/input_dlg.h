#ifndef DIALOG_INPUT_DLG_H_
#define DIALOG_INPUT_DLG_H_
#include <gtk/gtk.h>
#include <string>
#include "../window/window.h"
#include "../window/message.h"

namespace yage {
namespace dialog {
using namespace window;

class InputDlg {
public:

  ~InputDlg();
  InputDlg(const std::string &title);
  InputDlg(const std::string &title, Window &window);
  bool show(std::string &str);
  void set_message(const std::string &text);

private:
  GtkDialog *gtk_dialog_;
  GtkEntry *gtk_entry_;
  GtkLabel *gtk_label_;
  GtkTextBuffer *gtk_text_buffer_;

  static void exec_show(InputDlg *this_, std::string &yage_str, bool &ret);
  static void exec_set_message(InputDlg *this_, const std::string &text);
  static void exec_destroy(InputDlg *this_);
  static void exec_create(InputDlg *this_,
                          const char *title,
                          GtkWindow *parent);

  static gboolean msg_entry_on_enter_key(GtkWidget *widget,
                                   InputDlg *source);
  static gboolean msg_button_ok_on_click(GtkWidget *widget,InputDlg* source);
  static gboolean msg_button_cancel_on_click(GtkWidget* widget,InputDlg* source);

};

}  // namespace dialog
}  // namespace yage

#endif /* end of include guard: INPUT_DLG_H_3SLRDMQA */
