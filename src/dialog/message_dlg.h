#ifndef MESSAGE_H_S4GAKVJJ
#define MESSAGE_H_S4GAKVJJ
#include <gtk/gtk.h>
#include "../core/window.h"
#include "../core/message.h"

namespace yage {
namespace dialog {
using namespace core;

class MessageDlg {
public:
  enum button_type {
    button_type_none = 0,
    button_type_ok,
    button_type_close,
    button_type_cancel,
    button_type_yes_no,
    button_type_ok_cancel
  };

  enum icon_type {
    icon_type_none = 0,
    icon_type_info,
    icon_type_warning,
    icon_type_question,
    icon_type_error,
  };

  enum result_type{
      result_type_none = 0,
      result_type_reject,
      result_type_accept,
      result_type_ok,
      result_type_cancel,
      result_type_close,
      result_type_yes,
      result_type_no,
      result_type_apply,
      result_type_help,
  };

  ~MessageDlg();
  MessageDlg(button_type button, icon_type icon);
  MessageDlg(button_type button, icon_type icon, Window &window);

  void set_title(const char *title);
  void set_message(const char *msg);
  result_type show();

private:
  const size_t kBufferSize = 1024 * 8;
  GtkWidget *gtk_dialog_;

  static gboolean exec_show(gpointer *param);
  static gboolean exec_destroy(gpointer *param);
  static gboolean exec_create(gpointer *param);
  static gboolean exec_set_title(gpointer *param);
  static gboolean exec_set_message(gpointer *param);

};

}  // namespace dialog
}  // namespace yage

#endif /* end of include guard: MESSAGE_H_S4GAKVJJ */
