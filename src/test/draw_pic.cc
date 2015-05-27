#include "test.h"
#include "../window/window.h"
#include "../draw/canvas.h"
#include <string>

using namespace yage::window;
using namespace yage::draw;

void test_draw_pic()
{
  cout << "Please input the picture file path:";
  std::string file_path;
  std::cin >> file_path;
  Canvas canvas(file_path);
  int width,height;
  canvas.get_size(width,height);
  Window window(width,height);
  window.set_canvas(canvas);
  window.show();
  while(window.is_valid())
    g_usleep(1e6);
}
