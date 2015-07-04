#include "test.h"
#include "../dialog/message_dlg.h"
#include "../dialog/file_chooser_dlg.h"
#include "../dialog/color_chooser_dlg.h"
#include "../dialog/font_chooser_dlg.h"
#include "../dialog/input_dlg.h"
using namespace yage::dialog;

#ifdef _MSC_VER
#pragma warning(disable: 4566)
#endif

void test_dialog_msg(Window &w)
{
  MessageDlg msg_dlg(MessageDlg::button_type_yes_no, MessageDlg::icon_type_question, w);
  msg_dlg.set_title("<u>title</u>");
  msg_dlg.set_message("<i>message: press a button</i>");
  MessageDlg msg_dlg1(MessageDlg::button_type_ok, MessageDlg::icon_type_info, w);
  msg_dlg1.set_title("result");
  if (msg_dlg.show() == MessageDlg::result_type_yes) {
    msg_dlg1.set_message("yes");
  } else {
    msg_dlg1.set_message("no");
  }
  msg_dlg1.show();
}

void test_dialog_error(Window &w)
{
  MessageDlg msg_dlg(MessageDlg::button_type_close, MessageDlg::icon_type_error, w);
  msg_dlg.set_title("<u>title</u>");
  msg_dlg.set_message("<i>message: press a button</i>");
  msg_dlg.show();
}

void test_dialog_wraning(Window &w)
{
  MessageDlg msg_dlg(MessageDlg::button_type_ok_cancel, MessageDlg::icon_type_warning, w);
  msg_dlg.set_title("<u>title</u>");
  msg_dlg.set_message("<i>message: press a button</i>");
  msg_dlg.show();
}

void test_dialog_fc(FileChooserDlg::action_type type, Window &w)
{
  FileChooserDlg fc_dlg(type, "浏览文件", w);
  std::string path;
  if (fc_dlg.show(path)) {
    fprintf(stderr, "Path: %s\n", path.c_str());
  }
}

void test_dialog_input(Window &w)
{
  std::string msg = "测试对话框\n支持换行.";
  bool ok = true;
  while (ok) {
    InputDlg input_dlg("输入对话框", w);
    input_dlg.set_message(msg);
    ok = input_dlg.show(msg);
  }
}

void test_dialog_color_font(Window &w)
{
  ColorChooserDlg color_dlg("color", w);
  FontChooserDlg font_dlg("font", w);

  yage::draw::Color color;
  yage::draw::Font font;

  color_dlg.show(color);
  font_dlg.show(font);

  yage::draw::Text text("YaGE 我能吞下玻璃而不伤身体");
  text.position = yage::draw::Point(0, 0);
  Paint p;
  p.set_font_color(color);
  p.font = font;

  Canvas c(640, 480);
  w.set_canvas(c);
  c.draw_text(text,p);
  w.update();
}

void test_dialog()
{
  using namespace yage::dialog;
  Window w;
  w.set_title("对话框测试");
  w.show();
  Message msg;

  while (yage::window::poll(msg)) {
    if (msg.type != msg.type_kbd) continue;
    if (!msg.kbd.is_press) continue;

    switch (msg.kbd.keyval) {
      case 'a':
        test_dialog_msg(w);
        break;

      case 'b':
        test_dialog_fc(FileChooserDlg::action_type_open, w);
        break;

      case 'c':
        test_dialog_fc(FileChooserDlg::action_type_save, w);
        break;

      case 'd':
        test_dialog_fc(FileChooserDlg::action_type_create_folder, w);
        break;

      case 'e':
        test_dialog_fc(FileChooserDlg::action_type_select_folder, w);
        break;

      case 'f':
        test_dialog_color_font(w);
        break;

      case 'g':
        test_dialog_input(w);
        break;

      case 'h':
        test_dialog_error(w);
        break;

      case 'i':
        test_dialog_wraning(w);
        break;
    }
  }
}

