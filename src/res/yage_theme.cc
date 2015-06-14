#include "yage_theme.h"
#include "yage_theme_css.h"
#include "icon_yage_cancel.h"
#include "icon_yage_ok.h"
#include "icon_yage_edit_clear.h"
#include "icon_yage_question.h"
#include "icon_yage_information.h"
#include "icon_yage_close.h"
#include "icon_yage_error.h"
#include "icon_yage_warning.h"
#include "icon_yage_edit.h"
#include "icon_yage_delete.h"
#include "icon_yage_add.h"
#include "icon_yage_remove.h"
#include "icon_yage_search.h"
#include "icon_yage_folder.h"
#include "icon_yage_file.h"
#include "icon_yage_copy.h"
#include "icon_yage_cut.h"
#include "icon_yage_paste.h"
#include "icon_yage_select_all.h"
#include "icon_yage_open.h"
#include "icon_yage_save.h"
#define YAGE_ICON_NUM 25
namespace yage{
namespace res{

void init_yage_icon_theme()
{
  GtkIconFactory* icon_factory[YAGE_ICON_NUM];
  GtkIconSet* icon_set[YAGE_ICON_NUM];
  int i;
  for(i = 0;i < YAGE_ICON_NUM; i++)
  {
    icon_factory[i] = gtk_icon_factory_new();
    gtk_icon_factory_add_default(icon_factory[i]);
    switch(i)
    {
      case 0:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_ok, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_OK, icon_set[i]);
        break;
      case 1:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_cancel, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_CANCEL, icon_set[i]);
        break;
      case 2:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_edit_clear, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_CLEAR, icon_set[i]);
        break;
      case 3:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_cancel, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_NO, icon_set[i]);
        break;
      case 4:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_ok, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_YES, icon_set[i]);
        break;
      case 5:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_ok, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_APPLY, icon_set[i]);
        break;
      case 6:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_question, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_DIALOG_QUESTION, icon_set[i]);
        break;
      case 7:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_information, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_DIALOG_INFO, icon_set[i]);
        break;
      case 8:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_warning, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_DIALOG_WARNING, icon_set[i]);
        break;
      case 9:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_error, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_DIALOG_ERROR, icon_set[i]);
        break;
      case 10:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_close, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_CLOSE, icon_set[i]);
        break;
      case 11:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_edit, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_EDIT, icon_set[i]);
        break;
      case 12:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_delete, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_DELETE, icon_set[i]);
        break;
      case 13:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_add, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_ADD, icon_set[i]);
        break;
      case 14:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_remove, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_REMOVE, icon_set[i]);
        break;
      case 15:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_search, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_FIND, icon_set[i]);
        break;
      case 16:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_folder, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_DIRECTORY, icon_set[i]);
        break;
      case 17:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_file, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_FILE, icon_set[i]);
        break;
      case 18:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_copy, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_COPY, icon_set[i]);
        break;
      case 19:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_cut, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_CUT, icon_set[i]);
        break;
      case 20:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_paste, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_PASTE, icon_set[i]);
        break;
      case 21:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_select_all, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_SELECT_ALL, icon_set[i]);
        break;
      case 22:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_open, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_OPEN, icon_set[i]);
        break;
      case 23:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_save, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_SAVE, icon_set[i]);
        break;
      case 24:
        icon_set[i] = gtk_icon_set_new_from_pixbuf(gdk_pixbuf_new_from_inline(-1, binary_icon_yage_save, FALSE, nullptr));
        gtk_icon_factory_add(icon_factory[i], GTK_STOCK_SAVE_AS, icon_set[i]);
        break;
    }
    gtk_icon_set_unref(icon_set[i]);
    g_object_unref(icon_factory[i]);

  }
}

void init_yage_theme()
{
  //GtkCssProvider* css_provider = gtk_css_provider_get_named("YaGE", nullptr);
  GtkCssProvider* css_provider = gtk_css_provider_get_default();
  gtk_css_provider_load_from_data(css_provider, (const gchar*)binary_yage_theme_css, sizeof(binary_yage_theme_css), nullptr);
  gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(css_provider), GTK_STYLE_PROVIDER_PRIORITY_THEME);
  init_yage_icon_theme();
}

}
}
