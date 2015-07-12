#include "test.h"
#include "../draw/animation.h"

using namespace yage::draw;

// Test case URL: http://www.gif.im/em/1532.zip

void test_draw_anim(void) {
  const int kMaxX = 10;
  const int kMaxY = 10;
  const int kSizeX = 56;
  const int kSizeY = 56;
  Window w(kMaxX * kSizeX, kMaxY * kSizeY);
  w.show();

  char path[233];
  Animation *anim[kMaxX][kMaxY];

  for (int x = 0; x < kMaxX; ++x) {
    for (int y = 0; y < kMaxY; ++y) {
      int i = x * kMaxY + y;
      int pos_x = x * kSizeX;
      int pos_y = y * kSizeY;
      sprintf(path, "/home/hugh/tmp/gif/%d.gif", i);
      anim[x][y] = new Animation(w, pos_x, pos_y, path);
    }
  }

  yage::window::Message msg;
  while (yage::window::poll(msg)) {
    if (msg.type != msg.type_mouse) continue;
    if (msg.mouse.type != msg.mouse.type_press) continue;
    int x = static_cast<int>(msg.mouse.x / kSizeX);
    int y = static_cast<int>(msg.mouse.y / kSizeY);
    if (anim[x][y]) {
      delete anim[x][y];
      anim[x][y] = NULL;
    }
  }
}
