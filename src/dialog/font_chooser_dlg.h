#ifndef FONT_CHOOSER_DLG_H_NPSYKKMZ
#define FONT_CHOOSER_DLG_H_NPSYKKMZ
#include <gtk/gtk.h>
#include "../core/window.h"
#include "../core/message.h"
#include "../draw/font.h"

namespace yage {
namespace dialog {
using namespace core;

class FontChooserDlg {
public:

  ~FontChooserDlg();
  FontChooserDlg(const char *title);
  FontChooserDlg(const char *title, Window &window);
  bool show(yage::draw::Font &font);

private:
  GtkFontChooser *gtk_dialog_;

  static gboolean exec_show(gpointer *param);
  static gboolean exec_destroy(gpointer *param);
  static gboolean exec_create(gpointer *param);
};

}  // namespace dialog
}  // namespace yage



#endif /* end of include guard: FONT_CHOOSER_DLG_H_NPSYKKMZ */
