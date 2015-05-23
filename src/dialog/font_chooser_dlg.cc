#include "font_chooser_dlg.h"
#include "../yage.h"
#include "../util/encoding.h"

namespace yage {
namespace dialog {

FontChooserDlg::FontChooserDlg(const char *title)
{
  char *utf_8_title = yage::util::ansi_to_utf_8(title);
  runner_call(exec_create, this, const_cast<char *>(utf_8_title), nullptr);
  yage::util::free_string(utf_8_title);
}

FontChooserDlg::FontChooserDlg(const char *title, Window &window)
{
  char *utf_8_title = yage::util::ansi_to_utf_8(title);
  runner_call(exec_create, this, const_cast<char *>(utf_8_title),
              window.pro_get_gtk_window());
  yage::util::free_string(utf_8_title);
}

FontChooserDlg::~FontChooserDlg()
{
  runner_call(exec_destroy, this);
}

void FontChooserDlg::exec_destroy(FontChooserDlg *this_)
{
  if (this_->gtk_dialog_) {
    gtk_widget_destroy(GTK_WIDGET(this_->gtk_dialog_));
    this_->gtk_dialog_ = nullptr;
  }
}

void FontChooserDlg::exec_create(FontChooserDlg *this_,
                                 const char *title,
                                 GtkWindow *parent)
{
  this_->gtk_dialog_ = GTK_FONT_CHOOSER(
      gtk_font_chooser_dialog_new(title, parent));
}

void FontChooserDlg::exec_show(FontChooserDlg *this_,
                               yage::draw::Font &yage_font,
                               bool &ret)
{
  gint run_ret = gtk_dialog_run(GTK_DIALOG(this_->gtk_dialog_));
  if (run_ret == GTK_RESPONSE_OK) {
    ret = true;

    PangoFontDescription *pango_font = gtk_font_chooser_get_font_desc(
        this_->gtk_dialog_);
    yage_font.pro_set_pango_font(pango_font);

  } else {
    ret = false;
  }
  gtk_widget_hide(GTK_WIDGET(this_->gtk_dialog_));
}

bool FontChooserDlg::show(yage::draw::Font &font)
{
  bool ret;
  runner_call(exec_show, this, &font, &ret);
  return ret;
}

}  // namespace dialog
}  // namespace yage
