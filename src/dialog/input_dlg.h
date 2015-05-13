#ifndef INPUT_DLG_H_3SLRDMQA
#define INPUT_DLG_H_3SLRDMQA
#include <gtk/gtk.h>
#include <string>
#include "../core/window.h"
#include "../core/message.h"

namespace yage {
namespace dialog {
using namespace core;

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

  static gboolean exec_show(gpointer *param);
  static gboolean exec_destroy(gpointer *param);
  static gboolean exec_create(gpointer *param);
  static gboolean exec_set_message(gpointer *param);

  static gboolean msg_entry_on_key(GtkWidget *widget,
                                   GdkEvent *event,
                                   InputDlg *source);

};

}  // namespace dialog
}  // namespace yage

#endif /* end of include guard: INPUT_DLG_H_3SLRDMQA */
