#ifndef COLORCHOOSERDLG_H_YAXOUDVN
#define COLORCHOOSERDLG_H_YAXOUDVN
#include <gtk/gtk.h>
#include "../window/window.h"
#include "../window/message.h"
#include "../draw/color.h"

namespace yage {
namespace dialog {
using namespace window;

class ColorChooserDlg {
public:

  ~ColorChooserDlg();
  ColorChooserDlg(const char *title);
  ColorChooserDlg(const char *title, Window &window);
  bool show(yage::draw::Color &color);

private:
  GtkColorChooser *gtk_dialog_;

  static void exec_destroy(ColorChooserDlg *this_);
  static void exec_create(ColorChooserDlg *this_,
                          const char *title,
                          GtkWindow *parent);
  static void exec_show(ColorChooserDlg *this_,
                        yage::draw::Color &yage_color,
                        bool &ret);
};

}  // namespace dialog
}  // namespace yage

#endif /* end of include guard: COLORCHOOSERDLG_H_YAXOUDVN */
