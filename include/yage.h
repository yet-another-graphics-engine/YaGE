#ifndef YAGE_H_
#define YAGE_H_
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

struct yage_color_t {
  double r;
  double g;
  double b;
  double a;
};

void yage_init(int width, int height);
void yage_quit(void);
void yage_clear(void);

void yage_draw_pixel(double x, double y, yage_color_t color);

void yage_set_font(const char *family, int size, int bold, int italic);
void yage_set_fill_color(struct yage_color_t fill_color);
void yage_set_font_color(struct yage_color_t font_color);
void yage_set_border_color(struct yage_color_t border_color);
void yage_set_border_thickness(double thickness);

void yage_circle(double x, double y, double r);
void yage_circle_fill(double x, double y, double r);
void yage_circle_border(double x, double y, double r);

void yage_ellipse(double x, double y, double radius_x, double radius_y);
void yage_ellipse_fill(double x, double y, double radius_x, double radius_y);
void yage_ellipse_border(double x, double y, double radius_x, double radius_y);

void yage_rectangle(double x1, double y1, double x2, double y2);
void yage_rectangle_fill(double x1, double y1, double x2, double y2);
void yage_rectangle_border(double x1, double y1, double x2, double y2);

void yage_sector(double x, double y, double r, double angle_begin, double angle_end);
void yage_sector_fill(double x, double y, double r, double angle_begin, double angle_end);
void yage_sector_border(double x, double y, double r, double angle_begin, double angle_end);

void yage_arc_border(double x, double y, double angle_begin, double angle_end, double r);
void yage_line_border(double x1, double y1, double x2, double y2);

void yage_printf(double x, double y, const char *format, ...);


enum yage_message_type {
  YageNop = 0,
  YageKbd,
  YageMouse,
  YageWindow
};

enum yage_message_mouse_type {
  YageMousePress = 1,
  YageMouseRelease,
  YageMouseMove
};

enum yage_message_window_type {
  YageWindowEnter = 1,
  YageWindowLeave,
  YageWindowDestroy,
  YageWindowResize
};

struct yage_message_t {
  enum yage_message_type type;

  void *source;

  union {
    struct {
      bool is_press;
      uint32_t keyval;
      uint16_t keycode;

      bool is_modkey    : 1;
      bool modkey_alt   : 1;
      bool modkey_ctrl  : 1;
      bool modkey_shift : 1;
    } kbd;

    struct {
      double x, y;
      enum yage_message_mouse_type type;

      bool is_left      : 1;
      bool is_right     : 1;
      bool is_middle    : 1;

      bool modkey_alt   : 1;
      bool modkey_ctrl  : 1;
      bool modkey_shift : 1;
    } mouse;

    struct {
      enum yage_message_window_type type;
    } window;
  };
};

int yage_get_message(struct yage_message_t *msg, int wait_ms);
int  yage_get_key(void);

int  yage_dlg_font(const char *title);
int  yage_dlg_color(const char *title, struct yage_color_t *color);
char *yage_dlg_file_save(const char *title);
char *yage_dlg_file_open(const char *title);
void yage_dlg_message(const char *title, const char *message);

enum yage_dlg_button_t {
  kYageDlgButtonNone = 0,
  kYageDlgButtonOk,
  kYageDlgButtonClose,
  kYageDlgButtonCancel,
  kYageDlgButtonYesNo,
  kYageDlgButtonOkCancel
};

enum yage_dlg_icon_t {
  kYageDlgIconNone = 0,
  kYageDlgIconInfo,
  kYageDlgIconWarning,
  kYageDlgIconQuestion,
  kYageDlgIconError,
};

enum yage_dlg_result_t {
  kYageDlgResultNone = 0,
  kYageDlgResultReject,
  kYageDlgResultAccept,
  kYageDlgResultOk,
  kYageDlgResultCancel,
  kYageDlgResultClose,
  kYageDlgResultYes,
  kYageDlgResultNo,
  kYageDlgResultApply,
  kYageDlgResultHelp,
};

yage_dlg_result_t yage_dlg_question(const char *title,
                                    const char *message,
                                    yage_dlg_icon_t icon,
                                    yage_dlg_button_t button);

int yage_input_int(const char *title, const char *message);
double yage_input_double(const char *title, const char *message);
char *yage_input_line(const char *title, const char *message);
int yage_input_scanf(const char *title, const char *message, const char *format, ...);

#ifdef __cplusplus
}  // extern "C"
#endif
#endif
