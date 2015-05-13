#ifndef YAGE_GRAPHICS_H
#define YAGE_GRAPHICS_H

#ifndef _EGE_H_
#define _EGE_H_
#else
#error Please do not include "graphics.h" (Easy Graphics Engine version) before including "graphics.h" provided by YaGE
#endif


#ifndef _YAGE_DISABLE_BGI_WARNINGS
#ifdef _MSC_VER
#pragma message("Note: BGI-compatible functions are deprecated, use modern YaGE API instead.")
#else
#warning BGI-compatible functions are deprecated, use modern YaGE API instead.
#endif
#endif

/* main function redirect
 * please use extern "C" before macro*/
#define main yage_main

#ifdef __cplusplus
extern "C" {
#endif

/* Level 1 start */
typedef unsigned int color_t;

void initgraph(int width, int height);
void closegraph(void);
void cleardevice(void);
void clearviewport(void);

#define EGERGB(r, g, b)         ( ((r)<<16) | ((g)<<8) | (b))
enum COLORS {
    BLACK           = 0,
    BLUE            = EGERGB(0, 0, 0xA8),
    GREEN           = EGERGB(0, 0xA8, 0),
    CYAN            = EGERGB(0, 0xA8, 0xA8),
    RED             = EGERGB(0xA8, 0, 0),
    MAGENTA         = EGERGB(0xA8, 0, 0xA8),
    BROWN           = EGERGB(0xA8, 0xA8, 0),
    LIGHTGRAY       = EGERGB(0xA8, 0xA8, 0xA8),
    DARKGRAY        = EGERGB(0x54, 0x54, 0x54),
    LIGHTBLUE       = EGERGB(0x54, 0x54, 0xFC),
    LIGHTGREEN      = EGERGB(0x54, 0xFC, 0x54),
    LIGHTCYAN       = EGERGB(0x54, 0xFC, 0xFC),
    LIGHTRED        = EGERGB(0xFC, 0x54, 0x54),
    LIGHTMAGENTA    = EGERGB(0xFC, 0x54, 0xFC),
    YELLOW          = EGERGB(0xFC, 0xFC, 0x54),
    WHITE           = EGERGB(0xFC, 0xFC, 0xFC),
};
void setcolor(color_t color);
void setfillcolor(color_t color);

void arc(int x, int y, int startangle, int endangle, int radius);
void arcf(float x, float y, float startangle, float endangle, float radius);
void bar(int left, int top, int right, int bottom);
void circle(int x, int y, int radius);
void circlef(float x, float y, float radius);
void ellipse(int x, int y, int startangle, int endangle, int xradius, int yradius);
void ellipsef(float x, float y, float startangle, float endangle, float xradius, float yradius);
void fillellipse(int x, int y, int xradius, int yradius);
void fillellipsef(float x, float y, float xradius, float yradius);
void line(int x1, int y1, int x2, int y2);
void moveto(int x, int y);
void pieslice(int x, int y, int startangle, int endangle, int radius);
void pieslicef(float x, float y, float startangle, float endangle, float radius);
void putpixel(int x, int y, color_t color);
void rectangle(int left, int top, int right, int bottom);
void sector(int x, int y, int startangle, int endangle, int xradius, int yradius);
void sectorf(float x, float y, float startangle, float endangle, float xradius, float yradius);
void setlinewidth(int thickness);

void outtext(const char *text);
void outtextxy(int x, int y, const char *text);
void xyprintf(int x, int y, const char *format, ...);

int getch(void);
int inputbox_getline(const char *title, const char *text, char *buffer, int length);
int getInteger(const char *title);
double getFloat(const char *title);

void delay_ms(long miliseconds);
/* Level 1 end */

/* Level 3 temp start */

void lineto(int x, int y);

/* Level 3 temp end */

#ifdef __cplusplus
};
#endif

/* Temp code start */
#ifdef __cplusplus
typedef struct mouse_msg {
    unsigned int msg;
    int x;
    int y;
    bool is_move();
    bool is_down();
    bool is_up();
    bool is_left();
    bool is_mid();
    bool is_right();
    bool is_wheel();
} mouse_msg;

mouse_msg getmouse();
#endif
/* Temp code end */

#endif /* YAGE_GRAPHICS_H */
