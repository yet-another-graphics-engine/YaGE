#include "../../include/yage.h"
#include "../../include/graphics.h"

void test_api_bgi(void) {
  initgraph(640, 480);
  int lines[]={1,1,200,200,100,1,1,100};
  drawlines(2,lines);
  getch();
}
