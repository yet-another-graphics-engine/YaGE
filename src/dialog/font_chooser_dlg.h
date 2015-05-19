#ifndef DIALOG_FONT_CHOOSER_DLG_H_
#define DIALOG_FONT_CHOOSER_DLG_H_
#include <gtk/gtk.h>
#include "../window/window.h"
#include "../window/message.h"
#include "../draw/font.h"

namespace yage {
namespace dialog {
using namespace window;

class FontChooserDlg {
public:

  ~FontChooserDlg();
  FontChooserDlg(const char *title);
  FontChooserDlg(const char *title, Window &window);
  bool show(yage::draw::Font &font);

private:
  GtkFontChooser *gtk_dialog_;

  static void exec_destroy(FontChooserDlg *this_);
  static void exec_create(FontChooserDlg *this_,
                          const char *title,
                          GtkWindow *parent);
  static void exec_show(FontChooserDlg *this_,
                        yage::draw::Font &yage_font,
                        int &ret);
};

}  // namespace dialog
}  // namespace yage



#endif /* end of include guard: FONT_CHOOSER_DLG_H_NPSYKKMZ */
