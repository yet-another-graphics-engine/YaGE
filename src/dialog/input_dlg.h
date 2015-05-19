#ifndef INPUT_DLG_H_3SLRDMQA
#define INPUT_DLG_H_3SLRDMQA
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
  InputDlg(const char *title);
  InputDlg(const char *title, Window &window);
  bool show(std::string &str);
  void set_message(const char *text);

private:
  GtkDialog *gtk_dialog_;
  GtkEntry *gtk_entry_;
  GtkLabel *gtk_label_;

  static void exec_show(InputDlg *this_, std::string &yage_str, bool &ret);
  static void exec_set_message(InputDlg *this_, const char *text);
  static void exec_destroy(InputDlg *this_);
  static void exec_create(InputDlg *this_,
                          const char *title,
                          GtkWindow *parent);

  static gboolean msg_entry_on_key(GtkWidget *widget,
                                   GdkEvent *event,
                                   InputDlg *source);

};

}  // namespace dialog
}  // namespace yage

#endif /* end of include guard: INPUT_DLG_H_3SLRDMQA */
