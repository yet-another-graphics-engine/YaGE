#ifndef DIALOG_COLOR_CHOOSER_DLG_H_
#define DIALOG_COLOR_CHOOSER_DLG_H_
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
  ColorChooserDlg(const std::string &title);
  ColorChooserDlg(const std::string &title, Window &window);
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
