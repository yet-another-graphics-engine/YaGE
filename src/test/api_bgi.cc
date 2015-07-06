#include <cstdlib>
#include "../../include/graphics.h"

void test_api_bgi(void) {
    initgraph(640, 480);
    setcolor(BLACK);
    arc(50, 50, 0, 270, 25);
    setcolor(BLUE);
    arcf(50.0f, 100.0f, 90.0f, 360.0f, 25.0f);
    setfillcolor(RED);
    bar(100, 0, 125, 30);
    setcolor(GREEN);
    circle(125, 30, 25);
    setcolor(RED);
    circlef(150.0, 100.0, 25.0);
    setcolor(BLUE);
    ellipse(250, 30, 90, 360, 50, 25);
    fillellipsef(250, 30, 50, 25);
    setlinewidth(3);
    line(0, 0, 640, 480);
    setfillcolor(YELLOW);
    pieslice(300, 30, 45, 315, 25);
    moveto(200, 30);
    lineto(0, 200);
    int pixels[] = {0, 300, BLACK,
                    0, 302, BLUE,
                    0, 304, GREEN,
                    0, 306, LIGHTBLUE,
                    0, 308, DARKGRAY,
                    0, 310, CYAN
                   };
    putpixels(6, pixels);
    rectangle(100, 300, 400, 200);
    sector(500, 300, 0, 270, 80, 50);
    setcolor(BLACK);
    moveto(500, 200);
    outtext("YaGE BGI");
    char buf[256];
    inputbox_getline("YaGE BGI test", "Input some text to continue", buf, 256);
    outtextxy(0, 400, buf);
    int int_got = getInteger("Input an integer");
    double dbl_got = getFloat("Input an float number");
    char ch_got = getChar("Input a character");
    xyprintf(0, 420, "We have several numbers: int %d, char %c and double %lf", int_got, ch_got, dbl_got);
    int line_points[] = {500, 100,
                         450, 150,
                         500, 200,
                         550, 150
                        };
    drawlines(2, line_points);
    delay_ms(2000);
    drawpoly(4, line_points);
    fillpoly(4, line_points);
    mouse_msg msg;
    setfillcolor(GREEN);
    while (true) {
        msg = getmouse();
        if (msg.is_right()) {
            closegraph();
            exit(0);
        }
        if (!msg.is_move()) {
            continue;
        }
        fillellipse(msg.x, msg.y, 2, 2);
    }
}
