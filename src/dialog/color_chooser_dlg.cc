#include "color_chooser_dlg.h"
#include "../yage.h"

namespace yage {
namespace dialog {

ColorChooserDlg::ColorChooserDlg(const char *title)
{
  yage::core::gtk_runner.call(exec_create,
      {this, const_cast<char *>(title), nullptr});
}

ColorChooserDlg::ColorChooserDlg(const char *title, Window &window)
{
  yage::core::gtk_runner.call(exec_create,
      {this, const_cast<char *>(title), window.pro_get_gtk_window()});
}

ColorChooserDlg::~ColorChooserDlg()
{
  yage::core::gtk_runner.call(exec_destroy, {this});
}

gboolean ColorChooserDlg::exec_destroy(gpointer *param)
{
  auto this_ = reinterpret_cast<ColorChooserDlg *>(param[0]);

  if (this_->gtk_dialog_) gtk_widget_destroy(GTK_WIDGET(this_->gtk_dialog_));

  yage::core::gtk_runner.signal();
  return false;
}

gboolean ColorChooserDlg::exec_create(gpointer *param)
{
  auto this_ = reinterpret_cast<ColorChooserDlg *>(param[0]);
  auto title = reinterpret_cast<const char *>(param[1]);
  auto parent = reinterpret_cast<GtkWindow *>(param[2]);

  this_->gtk_dialog_ = GTK_COLOR_CHOOSER(gtk_color_chooser_dialog_new(title,
                                                                      parent));
  gtk_color_chooser_set_use_alpha(this_->gtk_dialog_, TRUE);

  yage::core::gtk_runner.signal();
  return false;
}

gboolean ColorChooserDlg::exec_show(gpointer *param)
{
  auto this_ = reinterpret_cast<ColorChooserDlg *>(param[0]);
  auto &yage_color = *reinterpret_cast<yage::draw::Color *>(param[1]);
  auto &ret = *reinterpret_cast<gint *>(param[2]);

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

  yage::core::gtk_runner.signal();
  return false;
}

bool ColorChooserDlg::show(yage::draw::Color &color)
{
  bool ret;
  gtk_runner.call(exec_show, {this, &color, &ret});
  return ret;
}

}  // namespace dialog
}  // namespace yage
