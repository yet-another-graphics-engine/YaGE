// BGI Compatibility Layer
#include "../window/window.h"
#include "../draw/canvas.h"
#include "../dialog/input_dlg.h"

#include <cstdarg>
#include <cstring>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#ifdef _MSC_VER
#pragma warning(disable: 4244)
#pragma warning(disable: 4800)
#endif

#ifdef __MINGW32__ // `vsnprintf` that MinGW provides uses MSVCRT library, which is not C99 compatible
#include "../util/snprintf.h"
#endif

static yage::window::Window *window = NULL;
static yage::draw::Canvas *canvas = NULL;
static yage::draw::Point canvas_position(0, 0);
static yage::draw::Paint paint;
//static yage::draw::Font simsun("SimSun", 12, false, false);
typedef unsigned int color_t;

extern "C" {

void initgraph(int width, int height) {
    window = new yage::window::Window();
    window->set_size(width, height);
    window->show();
    canvas = new yage::draw::Canvas(width, height);
    window->set_canvas(*canvas);
    window->update();
}

void closegraph(void) {
    window->hide();
    delete window;
    window = NULL;
    canvas = NULL;
}

void cleardevice(void) {
    canvas->clear_all();
}

void clearviewport(void) {
    fprintf(stderr, "WARNING: Not properly implemented because setviewport will be implemented later\n");
}

void setcolor(color_t color) {
    paint.set_line_color(yage::draw::Color(color));
    paint.set_font_color(yage::draw::Color(color));
}

void setfillcolor(color_t color) {
    paint.set_fill_color(yage::draw::Color(color));
    paint.set_background_color(yage::draw::Color(color));
}

void arcf(float x, float y, float startangle, float endangle, float radius) {
    paint.style = Paint::draw_style_stroke;
    yage::draw::EllipticSector ellipsec;
    yage::draw::Point center(x, y);
    ellipsec.center = center;
    ellipsec.startangle = startangle * M_PI / 180;
    ellipsec.endangle = endangle * M_PI / 180;
    ellipsec.xradius = radius;
    ellipsec.yradius = radius;

    canvas->draw_elliptical_sector(ellipsec, paint);
    window->update();
}

void arc(int x, int y, int startangle, int endangle, int radius) {
    arcf(x, y, startangle, endangle, radius);
}

void bar(int left, int top, int right, int bottom) {
    paint.style = Paint::draw_style_fill;

    yage::draw::Rect rect;
    yage::draw::Point a(left, top);
    yage::draw::Point b(right, bottom);
    rect.first = a;
    rect.second = b;

    canvas->draw_rect(rect, paint);
    window->update();
}

void circlef(float x, float y, float radius) {
    paint.style = Paint::draw_style_stroke;
    yage::draw::Circle circle1;
    yage::draw::Point center(x, y);
    circle1.center = center;
    circle1.radius = radius;
    circle1.center = center;

    canvas->draw_circle(circle1, paint);
    window->update();
}

void circle(int x, int y, int radius) {
    circlef(x, y, radius);
}

void ellipsef(float x, float y, float startangle, float endangle, float xradius, float yradius) {
    paint.style = Paint::draw_style_stroke;

    yage::draw::EllipticArc elliparc;
    yage::draw::Point center(x, y);
    elliparc.center = center;
    elliparc.startangle = startangle * M_PI / 180;
    elliparc.endangle = endangle * M_PI / 180;
    elliparc.xradius = xradius;
    elliparc.yradius = yradius;

    canvas->draw_elliptical_arc(elliparc, paint);
    window->update();
}

void ellipse(int x, int y, int startangle, int endangle, int xradius, int yradius) {
    ellipsef(x, y, startangle, endangle, xradius, yradius);
}

void fillellipsef(float x, float y, float xradius, float yradius) {
    paint.style = Paint::draw_style_fill;

    yage::draw::Ellipse ellipse1(yage::draw::Point(x, y), xradius, yradius);

    canvas->draw_ellipse(ellipse1, paint);
    window->update();
}

void fillellipse(int x, int y, int xradius, int yradius) {
    fillellipsef(x, y, xradius, yradius);
}

void line(int x1, int y1, int x2, int y2) {
    paint.style = Paint::draw_style_stroke;
    yage::draw::Line line1(yage::draw::Point(x1, y1),
                           yage::draw::Point(x2, y2));
    canvas->draw_line(line1, paint);
    window->update();
}

void pieslicef(float x, float y, float startangle, float endangle, float radius) {
    paint.style = Paint::draw_style_fill;

    yage::draw::EllipticSector ellipsec;
    yage::draw::Point center(x, y);
    ellipsec.center = center;
    ellipsec.startangle = startangle * M_PI / 180;
    ellipsec.endangle = endangle * M_PI / 180;
    ellipsec.xradius = radius;
    ellipsec.yradius = radius;

    canvas->draw_elliptical_sector(ellipsec, paint);
    window->update();
}

void moveto(int x, int y) {
    canvas_position.x=x;
    canvas_position.y=y;
}

void pieslice(int x, int y, int startangle, int endangle, int radius) {
    pieslicef(x, y, startangle, endangle, radius);
}

void putpixel(int x, int y, color_t color) {
    Paint p;
    p.style = Paint::draw_style_fill;
    p.set_fill_color(yage::draw::Color(color));

    yage::draw::Rect pixel;
    yage::draw::Point a(x - 0.5, y - 0.5);
    yage::draw::Point b(x + 0.5, y + 0.5);
    pixel.first = a;
    pixel.second= b;

    canvas->draw_rect(pixel, p);
    window->update();
}

void rectangle(int left, int top, int right, int bottom) {
    paint.style = Paint::draw_style_stroke;

    yage::draw::Rect rect;
    yage::draw::Point a(left, top);
    yage::draw::Point b(right, bottom);
    rect.first = a;
    rect.second= b;

    canvas->draw_rect(rect, paint);
    window->update();
}

void sectorf(float x, float y, float startangle, float endangle, float xradius, float yradius) {
    paint.style = Paint::draw_style_fill;

    yage::draw::EllipticSector ellipsec;
    yage::draw::Point center(x, y);
    ellipsec.center = center;
    ellipsec.startangle = startangle * M_PI / 180;
    ellipsec.endangle = endangle * M_PI / 180;
    ellipsec.xradius = xradius;
    ellipsec.yradius = yradius;

    canvas->draw_elliptical_sector(ellipsec, paint);
    window->update();
}

void sector(int x, int y, int startangle, int endangle, int xradius, int yradius) {
    sectorf(x, y, startangle, endangle, xradius, yradius);
}

void setlinewidth(int line_width) {
    paint.line_width = line_width;
}

void outtext(const char *text) {
    yage::draw::Text text1(text);
    text1.position = canvas_position;
    canvas->draw_text(text1, paint);
    window->update();
}

void outtextxy(int x, int y, const char *text) {
    yage::draw::Text text1(text);
    text1.position = yage::draw::Point(x, y);
    canvas->draw_text(text1, paint);
    window->update();
}

void xyprintf(int x, int y, const char *format, ...) {
    va_list args;
    char buf[512];
    va_start(args, format);
#ifdef _MSC_VER
#if _MSC_VER > 1300
    vsprintf_s(buf, 512, format, args);
#else
    _vsnprintf(buf, 512, format, args);
#endif
#else
    vsnprintf(buf, 512, format, args);
#endif
    va_end(args);
    yage::draw::Text text1(buf);
    text1.position = yage::draw::Point(x, y);
    canvas->draw_text(text1, paint);
    window->update();
}

int getch(void) {
    yage::window::Message msg;
    while(yage::window::poll(msg)) {
        if (msg.type == yage::window::Message::type_kbd) {
            return msg.kbd.keyval;
        }
    }
    return -1;
}

int inputbox_getline(const char *title, const char *text, char *buffer, int length) {
    yage::dialog::InputDlg dlg(title, *window);
    dlg.set_message(text);
    std::string content;
    dlg.show(content);
#if defined(_MSC_VER) && _MSC_VER > 1200
    strncpy_s(buffer, length, content.c_str(), _TRUNCATE);
#else
    strncpy(buffer, content.c_str(), length - 1);
#endif
    return 0;
}

int getInteger(const char *title) {
    yage::dialog::InputDlg dlg(title, *window);
    dlg.set_message("Input integer below");
    std::string content;
    dlg.show(content);
    std::istringstream str_stream;
    str_stream.str(content);
    int result;
    str_stream >> result;
    return result;
}

double getFloat(const char *title) {
    yage::dialog::InputDlg dlg(title, *window);
    dlg.set_message("Input float below");
    std::string content;
    dlg.show(content);
    std::istringstream str_stream;
    str_stream.str(content);
    float result;
    str_stream >> result;
    return result;
}

void delay_ms(long milliseconds) {
    #ifdef _WIN32
    Sleep(milliseconds);
    #else
    usleep(1000 * milliseconds);
    #endif
}

void lineto(int x, int y) {
    line(canvas_position.x, canvas_position.y, x, y);
}

/* Level 2 start */

void drawlines(int num_lines, const int points[]) {
    for(int i = 0; i < num_lines; ++i){
        line(points[4 * i], points[ 4 * i + 1 ],
             points[4 * i + 2 ], points[ 4 * i + 3 ]);
    }
}

void drawpoly(int num_points, const int *poly_points) {
    paint.style = Paint::draw_style_stroke;
    Poly poly;
    for (int i = 0; i < num_points; i++) {
        Point point(poly_points[2 * i], poly_points[2 * i + 1]);
        poly.vertex.push_back(point);
    }
    canvas->draw_poly(poly, paint);
    window->update();
}

void fillpoly(int num_points, const int *poly_points) {
    paint.style = Paint::draw_style_fill;
    Poly poly;
    for (int i = 0; i < num_points; i++) {
        Point point(poly_points[2 * i], poly_points[2 * i + 1]);
        poly.vertex.push_back(point);
    }
    canvas->draw_poly(poly, paint);
    window->update();
}

void putpixels(int num_points, int *points_and_colors) {
    for (int i = 0; i < num_points; i++) {
        putpixel(points_and_colors[3 * i], points_and_colors[3 * i + 1], points_and_colors[3 * i + 2]);
    }
}

void getString(char *buffer, int length, const char *title) {
    inputbox_getline(title, "Input a string", buffer, length);
}

char getChar(const char *text) {
    char buf[2];
    inputbox_getline("Input a char", text, buf, 2);
    return buf[0];
}

void getCoords(int tops[], int num_coords, char *title) {
    fprintf(stderr, "WARNING: Not implemented now.\n");
}

/* Level 2 end */

#ifdef __cplusplus
};
#endif

/* Temp code start */

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

bool mouse_msg::is_move() {
    return msg & 64;
}

bool mouse_msg::is_down() {
    return msg & 32;
}

bool mouse_msg::is_up() {
    return msg & 16;
}

bool mouse_msg::is_left() {
    return msg & 8;
}

bool mouse_msg::is_mid() {
    return msg & 4;
}

bool mouse_msg::is_right() {
    return msg & 2;
}

bool mouse_msg::is_wheel() {
    return msg & 1;
}

mouse_msg getmouse() {
    mouse_msg ege_msg;
	yage::window::Message msg;
	ege_msg.msg = 0;
	ege_msg.x = -1;
	ege_msg.y = -1;
    while(yage::window::poll(msg)) {
        if (msg.type == yage::window::Message::type_mouse) {
            ege_msg.x = static_cast<int>(msg.mouse.x);
            ege_msg.y = static_cast<int>(msg.mouse.y);
            ege_msg.msg += (msg.mouse.type == msg.mouse.type_move) << 6;
            ege_msg.msg += (msg.mouse.type == msg.mouse.type_press) << 5;
            ege_msg.msg += (msg.mouse.type == msg.mouse.type_release) << 4;
            ege_msg.msg += msg.mouse.is_left << 3;
            ege_msg.msg += msg.mouse.is_middle << 2;
            ege_msg.msg += msg.mouse.is_right << 1;
            return ege_msg;
        }
    }
	return ege_msg;
}

/* Temp code end */
