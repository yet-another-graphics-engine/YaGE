// BGI Compatibility Layer
#include "core/window.h"
#include "draw/canvas.h"
#include "dialog/input_dlg.h"

#include <cstdarg>
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

static yage::core::Window *window = nullptr;
static yage::draw::Canvas *canvas = nullptr;
static yage::draw::Point canvas_position(0, 0);
static yage::draw::Font simsun("SimSun", 12, false, false);
typedef unsigned int color_t;

extern "C" {

void initgraph(int width, int height) {
    window = new yage::core::Window();
    window->set_size(width, height);
    window->show();
    canvas = &window->pro_get_canvas();
}

void closegraph(void) {
    window->hide();
    delete window;
    window = nullptr;
    canvas = nullptr;
}

void cleardevice(void) {
    canvas->clear();
}

void clearviewport(void) {
    fprintf(stderr, "WARNING: Not properly implemented because setviewport will be implemented later\n");
}

void setcolor(color_t color) {
    canvas->set_fgcolor(yage::draw::Color(color));
}

void setfillcolor(color_t color) {
    canvas->set_bgcolor(yage::draw::Color(color));
}

void arcf(float x, float y, float startangle, float endangle, float radius) {
    yage::draw::EllipticSector ellipsec("");
    yage::draw::Point center(x, y);
    yage::draw::Color transparent(1, 1, 1, 0);
    ellipsec.set_bgcolor(transparent);
    ellipsec.set_fgcolor(canvas->get_fgcolor());
    ellipsec.set_thickness(canvas->get_thickness());
    ellipsec.set_center(center);
    ellipsec.set_startangle(startangle);
    ellipsec.set_endangle(endangle);
    ellipsec.set_xradius(radius);
    ellipsec.set_yradius(radius);
    canvas->draw_elliptical_sector(ellipsec);
}

void arc(int x, int y, int startangle, int endangle, int radius) {
    arcf(x, y, startangle, endangle, radius);
}

void bar(int left, int top, int right, int bottom) {
    yage::draw::Rect rect("");
    yage::draw::Point a(left, top);
    yage::draw::Point b(right, bottom);
    yage::draw::Color transparent(1, 1, 1, 0);
    rect.set_points(a, b);
    rect.set_bgcolor(canvas->get_bgcolor());
    rect.set_fgcolor(transparent);
    canvas->draw_rect(rect);
}

void circlef(float x, float y, float radius) {
    yage::draw::Circle circle1("");
    yage::draw::Point center(x, y);
    circle1.set_center(center);
    circle1.set_radius(radius);
    circle1.set_fgcolor(canvas->get_fgcolor());
    circle1.set_thickness(canvas->get_thickness());
    circle1.set_center(center);
    canvas->draw_circle(circle1);
}

void circle(int x, int y, int radius) {
    circlef(x, y, radius);
}

void ellipsef(float x, float y, float startangle, float endangle, float xradius, float yradius) {
    yage::draw::EllipticArc elliparc("");
    yage::draw::Point center(x, y);
    yage::draw::Color transparent(1, 1, 1, 0);
    elliparc.set_bgcolor(transparent);
    elliparc.set_fgcolor(canvas->get_fgcolor());
    elliparc.set_thickness(canvas->get_thickness());
    elliparc.set_center(center);
    elliparc.set_startangle(startangle);
    elliparc.set_endangle(endangle);
    elliparc.set_xradius(xradius);
    elliparc.set_yradius(yradius);
    canvas->draw_elliptical_arc(elliparc);
}

void ellipse(int x, int y, int startangle, int endangle, int xradius, int yradius) {
    ellipsef(x, y, startangle, endangle, xradius, yradius);
}

void fillellipsef(float x, float y, float xradius, float yradius) {
    yage::draw::Ellipse ellipse1("");
    yage::draw::Point center(x, y);
    yage::draw::Color transparent(1, 1, 1, 0);
    ellipse1.set_center(center);
	ellipse1.set_xradius(xradius);
	ellipse1.set_yradius(yradius);
    ellipse1.set_bgcolor(canvas->get_bgcolor());
    ellipse1.set_fgcolor(transparent);
    canvas->draw_ellipse(ellipse1);
}

void fillellipse(int x, int y, int xradius, int yradius) {
    fillellipsef(x, y, xradius, yradius);
}

void line(int x1, int y1, int x2, int y2) {
    yage::draw::Line line1("");
    line1.set_points(yage::draw::Point(x1, y1), yage::draw::Point(x2, y2));
    canvas->draw_line(line1);
}

void pieslicef(float x, float y, float startangle, float endangle, float radius) {
    yage::draw::EllipticSector ellipsec("");
    yage::draw::Point center(x, y);
    yage::draw::Color transparent(1, 1, 1, 0);
    ellipsec.set_bgcolor(canvas->get_bgcolor());
    ellipsec.set_fgcolor(transparent);
    ellipsec.set_center(center);
    ellipsec.set_startangle(startangle);
    ellipsec.set_endangle(endangle);
    ellipsec.set_xradius(radius);
    ellipsec.set_yradius(radius);
    canvas->draw_elliptical_sector(ellipsec);
}

void moveto(int x, int y) {
    canvas_position.setx(x);
    canvas_position.sety(y);
}

void pieslice(int x, int y, int startangle, int endangle, int radius) {
    pieslicef(x, y, startangle, endangle, radius);
}

void putpixel(int x, int y, color_t color) {
    yage::draw::Rect pixel("");
    yage::draw::Point a(x - 0.5, y - 0.5);
    yage::draw::Point b(x + 0.5, y + 0.5);
    yage::draw::Color transparent(1, 1, 1, 0);
    pixel.set_points(a,b);
    pixel.set_fgcolor(transparent);
    pixel.set_bgcolor(yage::draw::Color(color));
    pixel.set_thickness(canvas->get_thickness());
    canvas->draw_rect(pixel);
}

void rectangle(int left, int top, int right, int bottom) {
    yage::draw::Rect rect("");
    yage::draw::Point a(left, top);
    yage::draw::Point b(right, bottom);
    yage::draw::Color transparent(1, 1, 1, 0);
    rect.set_points(a, b);
    rect.set_bgcolor(transparent);
    rect.set_fgcolor(canvas->get_fgcolor());
    rect.set_thickness(canvas->get_thickness());
    canvas->draw_rect(rect);

}

void sectorf(float x, float y, float startangle, float endangle, float xradius, float yradius) {
    yage::draw::EllipticSector ellipsec("");
    yage::draw::Point center(x, y);
    yage::draw::Color transparent(1, 1, 1, 0);
    ellipsec.set_bgcolor(canvas->get_bgcolor());
    ellipsec.set_fgcolor(transparent);
    ellipsec.set_center(center);
    ellipsec.set_startangle(startangle);
    ellipsec.set_endangle(endangle);
    ellipsec.set_xradius(xradius);
    ellipsec.set_yradius(yradius);
    canvas->draw_elliptical_sector(ellipsec);
}

void sector(int x, int y, int startangle, int endangle, int xradius, int yradius) {
    sectorf(x, y, startangle, endangle, xradius, yradius);
}

void setlinewidth(int thickness) {
    canvas->set_thickness(thickness);
}

void outtext(const char *text) {
    yage::draw::Text text1(text, simsun);
    text1.set_position(canvas_position);
    text1.set_fgcolor(canvas->get_fgcolor());
    canvas->draw_text(text1);
}

void outtextxy(int x, int y, const char *text) {
    yage::draw::Text text1(text, simsun);
    text1.set_position(yage::draw::Point(x, y));
    text1.set_fgcolor(canvas->get_fgcolor());
    canvas->draw_text(text1);
}

void xyprintf(int x, int y, const char *format, ...) {
    va_list args;
    char buf[512];
    va_start(args, format);
#ifdef _MSC_VER
    sprintf_s(buf, 512, format, args);
#else
    snprintf(buf, 512, format, args);
#endif
    va_end(args);
    yage::draw::Text text1(buf, simsun);
    text1.set_position(yage::draw::Point(x, y));
    text1.set_fgcolor(canvas->get_fgcolor());
    canvas->draw_text(text1);
}

int getch(void) {
    yage::core::Message msg;
    while(yage::core::Window::poll(msg)) {
        if (msg.type == yage::core::Message::type_kbd) {
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
    #ifndef _MSC_VER
    strncpy(buffer, content.c_str(), length - 1);
    #else
    strncpy_s(buffer, length, content.c_str(), _TRUNCATE);
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
    line(canvas_position.getx(), canvas_position.gety(), x, y);
}

#ifdef __cplusplus
};
#endif

/* Temp code start */

typedef struct mouse_msg {
    unsigned int msg = 0;
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
    yage::core::Message msg;
    while(yage::core::Window::poll(msg)) {
        if (msg.type == yage::core::Message::type_mouse) {
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
	return mouse_msg();
}

/* Temp code end */