#include "test.h"

void test_draw(void)
{
  Window w;
  w.show();
  using namespace yage::draw;

  Canvas canvas(640,480);
  std::string pic_name = "";
  /*if (pic_name == "") {
	  fprintf(stderr, "Please specify the picture name as pic_name.\nPicture will not show if you do not change the variable\n");
  } else {
	  Canvas picture(pic_name);
	  Point origin(0, 0);
	  canvas.draw_canvas(picture, origin);
  }*/
  Point viewport1(100,100);
  Point viewport2(600,400);
  canvas.set_viewport(viewport1,viewport2);
  yage::draw::Ellipse e;
  Point point(300, 200);
  e.center = point;
  Color color(0, 1, 0, 1);
  e.bgcolor = color;
  Color color1(1, 0, 0, 1);
  e.fgcolor = color1;
  e.xradius = 100;
  e.yradius = 200;
  canvas.draw_ellipse(e);
  Point point2(500, 400);
  Rect rect;
  rect.first = point;
  rect.second = point2;
  rect.bgcolor = color1;
  rect.fgcolor = color;
  canvas.draw_rect(rect);
  Font times("Times New Roman", 12, true, true);
  Text text("Yet another Graphics Engine", times);
  Color yellow(1, 1, 0, 1);
  text.color = yellow;
  text.position = point;
  canvas.draw_text(text);

  w.set_canvas(&canvas);
  w.update_window();

  Message msg;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_mouse) continue;
    if (msg.mouse.type != msg.mouse.type_move) continue;
    if (!msg.mouse.is_left) continue;
  }
}

