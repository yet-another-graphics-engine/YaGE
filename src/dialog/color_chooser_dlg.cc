#include "color_chooser_dlg.h"
#include "../yage.h"
#include "../util/encoding.h"

namespace yage {
namespace dialog {

ColorChooserDlg::ColorChooserDlg(const char *title)
{
  char *utf_8_title = yage::util::ansi_to_utf_8(title);
  runner_call(exec_create, this, const_cast<char *>(utf_8_title), nullptr);
  yage::util::free_string(utf_8_title);
}

ColorChooserDlg::ColorChooserDlg(const char *title, Window &window)
{
  char *utf_8_title = yage::util::ansi_to_utf_8(title);
  runner_call(exec_create, this, const_cast<char *>(utf_8_title),
              window.pro_get_gtk_window());
  yage::util::free_string(utf_8_title);
}

ColorChooserDlg::~ColorChooserDlg()
{
  runner_call(exec_destroy, this);
}

void ColorChooserDlg::exec_destroy(ColorChooserDlg *this_)
{
  if (this_->gtk_dialog_) {
    gtk_widget_destroy(GTK_WIDGET(this_->gtk_dialog_));
    this_->gtk_dialog_ = nullptr;
  }
}

void ColorChooserDlg::exec_create(ColorChooserDlg *this_,
                                      const char *title,
                                      GtkWindow *parent)
{
  this_->gtk_dialog_ = GTK_COLOR_CHOOSER(
      gtk_color_chooser_dialog_new(title, parent));
  gtk_color_chooser_set_use_alpha(this_->gtk_dialog_, TRUE);
}

void ColorChooserDlg::exec_show(ColorChooserDlg *this_,
                                yage::draw::Color &yage_color,
                                bool &ret)
{
  gint run_ret = gtk_dialog_run(GTK_DIALOG(this_->gtk_dialog_));
  if (run_ret == GTK_RESPONSE_OK) {
    ret = true;

    GdkRGBA gdk_color;
    gtk_color_chooser_get_rgba(this_->gtk_dialog_, &gdk_color);
    yage_color.r = gdk_color.red;
    yage_color.g = gdk_color.green;
    yage_color.b = gdk_color.blue;
    yage_color.a = gdk_color.alpha;
  } else {
    ret = false;
  }
  gtk_widget_hide(GTK_WIDGET(this_->gtk_dialog_));
}

bool ColorChooserDlg::show(yage::draw::Color &color)
{
  bool ret;
  runner_call(exec_show, this, &color, &ret);
  return ret;
}

}  // namespace dialog
}  // namespace yage
