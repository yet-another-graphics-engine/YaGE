#ifndef COLORCHOOSERDLG_H_YAXOUDVN
#define COLORCHOOSERDLG_H_YAXOUDVN
#include <gtk/gtk.h>
#include "../core/window.h"
#include "../core/message.h"
#include "../util/color.h"

namespace yage {
namespace dialog {
using namespace core;

class ColorChooserDlg {
public:

  ~ColorChooserDlg();
  ColorChooserDlg(const char *title);
  ColorChooserDlg(const char *title, Window &window);
  bool show(yage::util::Color &color);

private:
  GtkColorChooser *gtk_dialog_;

  static gboolean exec_show(gpointer *param);
  static gboolean exec_destroy(gpointer *param);
  static gboolean exec_create(gpointer *param);
};

}  // namespace dialog
}  // namespace yage

#endif /* end of include guard: COLORCHOOSERDLG_H_YAXOUDVN */
