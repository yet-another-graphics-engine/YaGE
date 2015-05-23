#include "test.h"

using namespace yage::draw;

void test_draw_shape(void)
{
  Window w;
  w.show();
  w.set_resizable(true);
  Canvas canvas(640,480);
  std::string pic_name = "";

  Paint paint;
  Point viewport1(100,100);
  Point viewport2(600,400);
  paint.set_viewport(viewport1,viewport2);

  yage::draw::Ellipse e;
  Point point(300, 200);
  e.center = point;
  Color color(0, 1, 0, 1);
  paint.fill_color = color;
  Color color1(1, 0, 0, 1);
  paint.line_color = color1;
  e.xradius = 100;
  e.yradius = 200;
  canvas.draw_ellipse(e,paint);

  paint.set_viewport_full_canvas();
  Point point2(500, 400);
  Rect rect;
  rect.first = point;
  rect.second = point2;

  paint.fill_color=color1;
  paint.line_color=color;
  canvas.draw_rect(rect,paint);

  Font times("Times New Roman", 12, true, true);
  Text text("Yet another Graphics Engine", times);
  Color yellow(1, 1, 0, 1);
  paint.line_color=yellow;
  text.position = point;
  canvas.draw_text(text,paint);

  w.set_canvas(&canvas);
  w.update_window();

  Message msg;
  while (Window::poll(msg)) {
    if (msg.type != msg.type_mouse) continue;
    if (msg.mouse.type != msg.mouse.type_move) continue;
    if (!msg.mouse.is_left) continue;
  }
}

