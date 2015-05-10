#ifndef FILE_CHOOSER_DLG_H_CKHZY7EV
#define FILE_CHOOSER_DLG_H_CKHZY7EV
#include <string>
#include <gtk/gtk.h>
#include "../core/window.h"
#include "../core/message.h"

namespace yage {
namespace dialog {
using namespace core;

class FileChooserDlg {
public:
  enum action_type {
    action_type_open = 0,
    action_type_save,
    action_type_select_folder,
    action_type_create_folder,
  };

  ~FileChooserDlg();
  FileChooserDlg(action_type action, const char *title);
  FileChooserDlg(action_type action, const char *title, Window &window);
  bool show(std::string &str);

private:
  GtkFileChooser *gtk_dialog_;

  static gboolean exec_show(gpointer *param);
  static gboolean exec_destroy(gpointer *param);
  static gboolean exec_create(gpointer *param);
};

}  // namespace dialog
}  // namespace yage

#endif /* end of include guard: FILE_CHOOSER_DLG_H_CKHZY7EV */
