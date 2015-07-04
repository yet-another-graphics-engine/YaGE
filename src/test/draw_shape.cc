#include "test.h"
#include <math.h>

using namespace yage::draw;

void test_draw_shape(void)
{
  Window w(640,480);
  //w.set_resizable(true);
  w.show();
  int width,height;
  w.set_size(-1,-1);
  w.get_size(width,height);
  printf("window_width=%d, window_height=%d\n", width, height);
  w.set_resizable(true);
  Canvas canvas(1024,576);
  std::string pic_name = "";

  Paint paint;
  paint.style = Paint::draw_style_stroke_fill;
  Point viewport1(100,100);
  Point viewport2(600,400);
  //paint.set_viewport(viewport1, viewport2);
  //paint.set_translate(viewport1.x, viewport1.y);
  //paint.set_rotate(M_PI / 4);
  paint.set_scale(1.5, 1.5);

  yage::draw::Ellipse e;
  Point point(300, 200);
  e.center = point;
  Color color(0, 1, 0, 1);
  Color color1(1, 0, 0, 1);
  paint.set_line_color_linear_gradient(LinearGradientColor(Color(1, 1, 1, 1),color1,
                                                           Point(0, 0), Point(0, 576)));
  paint.set_fill_color_linear_gradient(LinearGradientColor(Color(1, 1, 1, 1),color,
                                                           Point(0, 0), Point(0, 576)));
  e.xradius = 100;
  e.yradius = 200;
  canvas.draw_ellipse(e,paint);
  Canvas canvas2 = canvas;

  Point point2(500, 400);
  Rect rect;
  rect.first = point;
  rect.second = point2;

  //paint.set_fill_color(color1);
  paint.set_fill_color_linear_gradient(LinearGradientColor(color1, Color(1, 1, 1, 1),
                                                           point, point2));
  paint.set_line_color(color);
  canvas.draw_rect(rect,paint);

  Font times("Times New Roman", 12, true, true);
  paint.font = times;
  Text text("Yet another Graphics Engine");
  Color yellow(1, 1, 0, 1);
  paint.set_font_color(yellow);
  text.position = point;
  canvas.draw_text(text,paint);

  w.set_canvas(canvas);
  w.update();

  Message msg;
  while (yage::window::poll(msg)) {
    if (msg.type != msg.type_mouse) continue;
    if (msg.mouse.type != msg.mouse.type_move) continue;
    if (!msg.mouse.is_left) continue;
  }
}

