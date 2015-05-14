#include "core/window.h"
#include "draw/canvas.h"
#include "draw/color.h"
#include "platform/player.h"
#include "dialog/message_dlg.h"
#include "dialog/file_chooser_dlg.h"
#include "dialog/color_chooser_dlg.h"
#include "dialog/font_chooser_dlg.h"
#include "dialog/input_dlg.h"

#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace yage::core;
using namespace yage::dialog;
extern "C" int yage_main(void);

#define P_PROP(type, name, format) fprintf(stderr, #name"="#format", ", msg.type.name)
#define P_NAME(type) \
  case msg.type:\
  fprintf(stderr, #type ": ")

#define P_STOP() \
  fprintf(stderr, "\n"); \
break

static void sleep_sec(int seconds) {
#ifdef _WIN32
  Sleep(1000 * seconds);
#else
  sleep(seconds);
#endif
}


void test_message()
{
  Window w;
  w.show();

  Message msg;
  while (Window::poll(msg)) {
    switch (msg.type) {
      P_NAME(type_nop);
      P_STOP();

      P_NAME(type_kbd);
      P_PROP(kbd, is_press, %d);
      P_PROP(kbd, keyval, %u);
      P_PROP(kbd, keycode, %u);
      P_PROP(kbd, is_modkey, %u);
      P_PROP(kbd, modkey_alt, %u);
      P_PROP(kbd, modkey_ctrl, %u);
      P_PROP(kbd, modkey_shift, %u);
      P_STOP();

      P_NAME(type_mouse);
      P_PROP(mouse, x, %.1lf);
      P_PROP(mouse, y, %.1lf);
      P_PROP(mouse, type, %d);
      P_PROP(mouse, is_left, %u);
      P_PROP(mouse, is_right, %u);
      P_PROP(mouse, is_middle, %u);
      P_PROP(mouse, modkey_alt, %u);
      P_PROP(mouse, modkey_ctrl, %u);
      P_PROP(mouse, modkey_shift, %u);
      P_STOP();

      P_NAME(type_window);
      P_PROP(window, type, %d);
      P_STOP();

      default:
      break;
    }
  }
  fprintf(stderr, "test_message: Bye!\n");
}

void test_window_count(void)
{
  Window w;
  w.show();
  w.set_title("Window count test");
  char buf[20];
  int n = 0;

  Message msg;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_mouse) continue;
    if (msg.mouse.type != msg.mouse.type_press) continue;
    if (msg.mouse.is_left) {
      Window *new_win = new Window;
      new_win->show();
      #ifndef _MSC_VER
      snprintf(buf, sizeof(buf), "Window %d", ++n);
      #else
      _snprintf_s(buf, _countof(buf), sizeof(buf), "Window %d", ++n);
      #endif
      new_win->set_title(buf);
    }
    if (msg.mouse.is_right) msg.source->destroy();
  }
  fprintf(stderr, "test_window_count: Bye!\n");
}

void test_draw(void)
{
  Window w;
  w.show();
  using namespace yage::draw;

  Canvas& canvas = w.pro_get_canvas();
  std::string pic_name = "";
  if (pic_name == "") {
	  fprintf(stderr, "Please specify the picture name as pic_name.\nPicture will not show if you do not change the variable");
  } else {
	  Canvas picture(pic_name);
	  Point origin(0, 0);
	  canvas.draw_canvas(picture, origin);
  }
  yage::draw::Ellipse e("");
  Point point(300, 200);
  e.set_center(point);
  Color color(1, 0, 0, 1);
  e.set_bgcolor(color);
  Color color1(0, 1, 0, 1);
  e.set_fgcolor(color1);
  e.set_xradius(100);
  e.set_yradius(200);
  canvas.draw_ellipse(e);
  Point point2(500, 400);
  Rect rect("");
  rect.set_points(point, point2);
  rect.set_bgcolor(color1);
  rect.set_fgcolor(color);
  canvas.draw_rect(rect);
  Font times("Times New Roman", 12, true, true);
  Text text("Yet another Graphics Engine", times);
  Color yellow(1, 1, 0, 1);
  text.set_color(yellow);
  text.set_position(point);
  canvas.draw_text(text);

  Message msg;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_mouse) continue;
    if (msg.mouse.type != msg.mouse.type_move) continue;
    if (!msg.mouse.is_left) continue;
  }
}

void test_resize()
{
  Window w;
  bool resize = false;
  w.show();
  int x = 300, y = 300;

  Message msg;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_kbd) continue;
    if (!msg.kbd.is_press) continue;

    switch (msg.kbd.keyval) {
      case 't':
        resize = !resize;
        w.set_resizable(resize);
        fprintf(stderr, "Allow resize: %d\n", resize);
        break;

      case 'x':
        x -= 100;
        w.set_size(x, y);
        break;

      case 'X':
        x += 100;
        w.set_size(x, y);
        break;

      case 'y':
        y -= 100;
        w.set_size(x, y);
        break;

      case 'Y':
        y += 100;
        w.set_size(x, y);
        break;

      case 'q':
        fprintf(stderr, "x = %d, y = %d, ", x, y);
        w.get_size(x, y);
        fprintf(stderr, "nx = %d, ny = %d\n", x, y);
        break;

      case '!':
        w.hide();
        sleep_sec(1);
        w.show();
    }
  }
}

void test_fix_size()
{
  Window w;
  w.show();
  Message msg;

  Window *t = nullptr;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_kbd) continue;
    if (!msg.kbd.is_press) continue;

    switch (msg.kbd.keyval) {
      case 'a':
        if (t) delete t;
        t = new Window;
        t->show();
        fprintf(stderr, "show\n");
        break;

      case 'b':
        if (t) delete t;
        t = new Window;
        t->show();
        t->set_size(100, 200);
        fprintf(stderr, "show, set_size\n");
        break;

      case 'c':
        if (t) delete t;
        t = new Window;
        t->set_resizable(true);
        t->set_size(100, 200);
        t->show();
        fprintf(stderr, "set_res, set_size, show\n");
        break;

      case 'd':
        if (t) delete t;
        t = new Window;
        t->set_size(100, 200);
        t->set_resizable(true);
        t->show();
        fprintf(stderr, "set_size, set_res, show\n");
        break;

      case 'e':
        if (t) delete t;
        t = new Window;
        t->set_size(100, 200);
        t->show();
        t->set_resizable(true);
        fprintf(stderr, "set_size, show, set_res\n");
        break;

      case 'f':
        if (t) delete t;
        t = new Window;
        t->set_resizable(true);
        t->show();
        t->set_size(100, 200);
        fprintf(stderr, "set_res, show, set_size\n");
        break;

      case 'g':
        if (t) delete t;
        t = new Window;
        t->show();
        t->set_resizable(true);
        t->set_size(100, 200);
        fprintf(stderr, "show, set_res, set_size\n");
        break;

      case 'h':
        if (t) delete t;
        t = new Window;
        t->show();
        t->set_size(100, 200);
        t->set_resizable(true);
        fprintf(stderr, "show, set_size, set_res\n");
        break;

    }
  }
}

void test_dialog_msg(Window &w)
{
  MessageDlg msg_dlg(MessageDlg::button_type_yes_no, MessageDlg::icon_type_question, w);
  msg_dlg.set_title("<u>title</u>");
  msg_dlg.set_message("<i>message: press a button</i>");
  MessageDlg msg_dlg1(MessageDlg::button_type_ok, MessageDlg::icon_type_info);
  msg_dlg1.set_title("result");
  if (msg_dlg.show() == MessageDlg::result_type_yes) {
    msg_dlg1.set_message("yes");
  } else {
    msg_dlg1.set_message("no");
  }
  msg_dlg1.show();
}

void test_dialog_fc(FileChooserDlg::action_type type, Window &w)
{
  FileChooserDlg fc_dlg(type, "fc_dlg", w);
  std::string path;
  if (fc_dlg.show(path)) {
    fprintf(stderr, "Path: %s\n", path.c_str());
  }
}

void test_dialog_input(Window &w)
{
  std::string msg = "Aloha World!";
  bool ok = true;
  while (ok) {
    InputDlg input_dlg("input_dlg", w);
    input_dlg.set_message(msg.c_str());
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

  yage::draw::Text text("Yet another Graphics Engine", font);
  text.set_position(yage::draw::Point(0, 0));
  text.set_color(color);

  w.pro_get_canvas().draw_text(text);
}

void test_dialog()
{
  using namespace yage::dialog;
  Window w;
  w.show();
  Message msg;

  while (Window::poll(msg)) {
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
    }
  }
}

void test_audio(void) {
    using yage::platform::Player;
    std::cerr << "Load file IGNITE from Internet" << std::endl;
    Player *player = Player::create_player("https://kirito.me/ignite.mp3");
    std::cerr << "Play IGNITE" << std::endl;
    player->play();
    sleep_sec(5);
    std::cerr << "Load file Date A Live from Internet" << std::endl;
    Player *player2 = Player::create_player("https://kirito.me/date_a_live.mp3");
    std::cerr << "Play Date A Live" << std::endl;
    player2->play();
    sleep_sec(3);
    std::cerr << "Pause IGNITE" << std::endl;
    player->pause();
    sleep_sec(3);
    player->play();
    std::cerr << "Resume IGNITE" << std::endl;
    sleep_sec(3);
    std::cerr << "Stop IGNITE" << std::endl;
    player->stop();
    std::cerr << "Play IGNITE" << std::endl;
    player->play();
    sleep_sec(3);
    std::cerr << "Destroy music IGNITE object" << std::endl;
    delete player;
    sleep_sec(2);
    std::cerr << "Stop Date A Live" << std::endl;
    player2->stop();
    std::cerr << "Destroy music Date A Live object" << std::endl;
    delete player2;
}

int yage_main()
{
  test_draw();
  return 0;
}
