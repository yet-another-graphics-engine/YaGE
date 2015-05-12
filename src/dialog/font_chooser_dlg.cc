#include "font_chooser_dlg.h"
#include "../yage.h"

namespace yage {
namespace dialog {

FontChooserDlg::FontChooserDlg(const char *title)
{
  yage::core::gtk_runner.call(exec_create,
      {this, const_cast<char *>(title), nullptr});
}

FontChooserDlg::FontChooserDlg(const char *title, Window &window)
{
  yage::core::gtk_runner.call(exec_create,
      {this, const_cast<char *>(title), window.pro_get_gtk_window()});
}

FontChooserDlg::~FontChooserDlg()
{
  yage::core::gtk_runner.call(exec_destroy, {this});
}

gboolean FontChooserDlg::exec_destroy(gpointer *param)
{
  auto this_ = reinterpret_cast<FontChooserDlg *>(param[0]);

  if (this_->gtk_dialog_) gtk_widget_destroy(GTK_WIDGET(this_->gtk_dialog_));

  yage::core::gtk_runner.signal();
  return false;
}

gboolean FontChooserDlg::exec_create(gpointer *param)
{
  auto this_ = reinterpret_cast<FontChooserDlg *>(param[0]);
  auto title = reinterpret_cast<const char *>(param[1]);
  auto parent = reinterpret_cast<GtkWindow *>(param[2]);

  this_->gtk_dialog_ = GTK_FONT_CHOOSER(gtk_font_chooser_dialog_new(title,
                                                                    parent));

  yage::core::gtk_runner.signal();
  return false;
}

gboolean FontChooserDlg::exec_show(gpointer *param)
{
  auto this_ = reinterpret_cast<FontChooserDlg *>(param[0]);
  auto &yage_font = *reinterpret_cast<yage::draw::Font *>(param[1]);
  auto &ret = *reinterpret_cast<gint *>(param[2]);

  gint run_ret = gtk_dialog_run(GTK_DIALOG(this_->gtk_dialog_));
  if (run_ret == GTK_RESPONSE_OK) {
    ret = true;

    PangoFontDescription *pango_font = gtk_font_chooser_get_font_desc(
        this_->gtk_dialog_);
    yage_font.pro_set_pango_font(pango_font);

  } else {
    ret = false;
  }

  yage::core::gtk_runner.signal();
  return false;
}

bool FontChooserDlg::show(yage::draw::Font &font)
{
  bool ret;
  gtk_runner.call(exec_show, {this, &font, &ret});
  return ret;
}

}  // namespace dialog
}  // namespace yage
