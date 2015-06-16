/**
 * @file yage.h
 * @brief \~english Declaration for exported YaGE API.
 *        \~chinese YaGE 的导出 API 声明。
 */
#ifndef YAGE_H_
#define YAGE_H_
#include "stdint.h"

/**
 * \~english @brief main function redirect
 * DO NOT INCLUDE THIS HEADER TO WRITE PROGRAM THAT DO NOT LINK TO YAGE
 *
 * \~chinese @brief main 函数重定向
 * 请勿在不链接到 YaGE 的程序中包含此头文件
 */
#define main(...) yage_main(int argc, char *argv[])

#ifdef __cplusplus
extern "C" {
#endif

int yage_main(int argc, char *argv[]);

/**
 * \~english @brief An object holding color information.
 * \~chinese @brief 存储颜色信息的结构体。
 */
struct yage_color_t {
  double r; ///< \~english Red, range: 0.0 to 1.0
            ///< \~chinese 红色，区间为 0.0 至 1.0
  double g; ///< \~english Green, range: 0.0 to 1.0
            ///< \~chinese 绿色，区间为 0.0 至 1.0
  double b; ///< \~english Blue, range: 0.0 to 1.0
            ///< \~chinese 蓝色，区间为 0.0 至 1.0
  double a; ///< \~english Alpha, range: 0.0 (transparent) to 1.0 (nontransparent)
            ///< \~chinese 透明度，区间为 0.0（透明）至 1.0（不透明）
};

/**
 * \~english @brief Initialize the drawing components and create a fix-sized window.
 * @param width  the width of the window to create
 * @param height the height of the window to create
 *
 * \~chinese @brief 初始化绘图组件，并创建一个指定大小的窗口。
 * @param width  新窗口的宽度
 * @param height 新窗口的高度
 */
void yage_init(int width, int height);

/**
 * \~english @brief Close all windows and quit app.
 * \~chinese @brief 关闭全部窗口并退出程序。
 */
void yage_quit(void);

/**
 * \~english @brief Clean the canvas.
 *
 * Fill the whole canvas with background color.
 * \see yage_set_background_color
 *
 * \~chinese @brief 清空画布内容。
 *
 * 将整个画布填充为背景色。
 * \see yage_set_background_color
 */
void yage_clear(void);

/**
 * \~english @brief Draw specified color to a pixel.
 * @param x       the X coordinate of the pixel
 * @param y       the Y coordinate of the pixel
 * @param color   the color to set
 *
 * \~chinese @brief 在指定位置的像素上填充颜色。
 * @param x       像素的 X 坐标
 * @param y       像素的 Y 坐标
 * @param color   欲填充的颜色
 */
void yage_draw_pixel(double x, double y, yage_color_t color);

/**
 * \~english @brief Set the font family, size and style of font.
 * @param family  The family of the font. Use NULL to skip this setting
 * @param size    The size of the font. Use a negative number to skip this setting
 * @param bold    Pass 0 for nonbold font, >0 for bold font, <0 to skip this setting
 * @param italic  Pass 0 for nonitalic font, >0 for italic font, <0 to skip this setting
 *
 * \~chinese @brief 设置字体名称、大小和样式。
 * @param family  字体的名称。传入 NULL 以跳过本项设置
 * @param size    字体的大小。传入一个负数以跳过本项设置
 * @param bold    传入 0 关闭粗体， >0 打开粗体， <0 跳过本项设置
 * @param italic  传入 0 关闭斜体， >0 打开斜体， <0 跳过本项设置
 */
void yage_set_font(const char *family, int size, int bold, int italic);

/**
 * \~english @brief Set the fill color in shapes.
 * @param fill_color The new fill color
 * \see yage_set_border_color
 *
 * \~chinese @brief 设置形状里填充的颜色。
 * @param fill_color 新的填充色
 * \see yage_set_border_color
 */
void yage_set_fill_color(struct yage_color_t fill_color);

/**
 * \~english @brief Set the font color.
 * @param font_color The new font color
 *
 * \~chinese @brief 设置字体的颜色。
 * @param font_color 新的字体色
 */
void yage_set_font_color(struct yage_color_t font_color);

/**
 * \~english @brief Set the background color.
 * @param background_color The new background color
 * \see yage_clear
 *
 * \~chinese @brief 设置背景色。
 * @param background_color 新的背景色
 * \see yage_clear
 *
 */
void yage_set_background_color(struct yage_color_t background_color);

/**
 * \~english @brief Set the border color of shapes.
 * @param border_color The new border color
 * \see yage_set_fill_color
 *
 * \~chinese @brief 设置图形边框的颜色。
 * @param border_color 新的边框颜色
 * \see yage_set_fill_color
 */
void yage_set_border_color(struct yage_color_t border_color);

/**
 * \~english @brief Set the border thickness of shapes.
 * @param thickness The new border thickness
 *
 * \~chinese @brief 设置图形边框的粗细。
 * @param thickness 新的边框粗细
 */
void yage_set_border_thickness(double thickness);

/**
 * \~english @brief Draw border and fill a circle.
 * @param x  the X coordinate of the center of the circle
 * @param y  the Y coordinate of the center of the circle
 * @param r  the radius of the circle
 *
 * \~chinese @brief 画边框并填充圆。
 * @param x  圆心的 X 坐标
 * @param y  圆心的 Y 坐标
 * @param r  圆的半径
 */
void yage_circle(double x, double y, double r);

/**
 * \~english @brief Fill a circle, don't draw border.
 * @param x  the X coordinate of the center of the circle
 * @param y  the Y coordinate of the center of the circle
 * @param r  the radius of the circle
 *
 * \~chinese @brief 填充圆，不画边框。
 * @param x  圆心的 X 坐标
 * @param y  圆心的 Y 坐标
 * @param r  圆的半径
 */
void yage_circle_fill(double x, double y, double r);

/**
 * \~english @brief Draw border of a circle, don't fill.
 * @param x  the X coordinate of the center of the circle
 * @param y  the Y coordinate of the center of the circle
 * @param r  the radius of the circle
 *
 * \~chinese @brief 画圆的边框，不要填充。
 * @param x  圆心的 X 坐标
 * @param y  圆心的 Y 坐标
 * @param r  圆的半径
 */
void yage_circle_border(double x, double y, double r);

/**
 * \~english @brief Draw border and fill an ellipse.
 * @param x         the X coordinate of the center of the ellipse
 * @param y         the Y coordinate of the center of the ellipse
 * @param radius_x  the X radius of the ellipse
 * @param radius_y  the Y radius of the ellipse
 *
 * \~chinese @brief 画边框并填充椭圆。
 * @param x         椭圆圆心的 X 坐标
 * @param y         椭圆圆心的 Y 坐标
 * @param radius_x  椭圆的 X 轴半径坐标
 * @param radius_y  椭圆的 Y 轴半径坐标
 */
void yage_ellipse(double x, double y, double radius_x, double radius_y);

/**
 * \~english @brief Fill an ellipse, don't draw border.
 * @param x         the X coordinate of the center of the ellipse
 * @param y         the Y coordinate of the center of the ellipse
 * @param radius_x  the X radius of the ellipse
 * @param radius_y  the Y radius of the ellipse
 *
 * \~chinese @brief 填充椭圆，不画边框。
 * @param x         椭圆圆心的 X 坐标
 * @param y         椭圆圆心的 Y 坐标
 * @param radius_x  椭圆的 X 轴半径坐标
 * @param radius_y  椭圆的 Y 轴半径坐标
 */
void yage_ellipse_fill(double x, double y, double radius_x, double radius_y);

/**
 * \~english @brief Draw border of an ellipse, don't fill.
 * @param x         the X coordinate of the center of the ellipse
 * @param y         the Y coordinate of the center of the ellipse
 * @param radius_x  the X radius of the ellipse
 * @param radius_y  the Y radius of the ellipse
 *
 * \~chinese @brief 画椭圆边框，不要填充。
 * @param x         椭圆圆心的 X 坐标
 * @param y         椭圆圆心的 Y 坐标
 * @param radius_x  椭圆的 X 轴半径坐标
 * @param radius_y  椭圆的 Y 轴半径坐标
 */
void yage_ellipse_border(double x, double y, double radius_x, double radius_y);

/**
 * \~english @brief Draw border and fill a rectangle.
 * @param x1        the X coordinate of a point on one diagonal line.
 * @param y1        the Y coordinate of the point on one diagonal line.
 * @param x2        the X coordinate of another point on the same diagonal line.
 * @param y2        the Y coordinate of the point on the same diagonal line.
 *
 * \~chinese @brief 画矩形的边框并填充。
 * @param x1        矩形某条对角线上一点的 X 坐标
 * @param y1        矩形某条对角线上一点的 Y 坐标
 * @param x2        矩形同一条对角线上另一点的 X 坐标
 * @param y2        矩形同一条对角线上另一点的 Y 坐标
 */
void yage_rectangle(double x1, double y1, double x2, double y2);

/**
 * \~english @brief Fill a rectangle, don't fill.
 * @param x1        the X coordinate of a point on one diagonal line.
 * @param y1        the Y coordinate of the point on one diagonal line.
 * @param x2        the X coordinate of another point on the same diagonal line.
 * @param y2        the Y coordinate of the point on the same diagonal line.
 *
 * \~chinese @brief 填充矩形，不要画边框。
 * @param x1        矩形某条对角线上一点的 X 坐标
 * @param y1        矩形某条对角线上一点的 Y 坐标
 * @param x2        矩形同一条对角线上另一点的 X 坐标
 * @param y2        矩形同一条对角线上另一点的 Y 坐标
 */
void yage_rectangle_fill(double x1, double y1, double x2, double y2);

/**
 * \~english @brief Draw border of a rectangle, don't fill.
 * @param x1        the X coordinate of a point on one diagonal line.
 * @param y1        the Y coordinate of the point on one diagonal line.
 * @param x2        the X coordinate of another point on the same diagonal line.
 * @param y2        the Y coordinate of the point on the same diagonal line.
 *
 * \~chinese @brief 画矩形边框，不要填充。
 * @param x1        矩形某条对角线上一点的 X 坐标
 * @param y1        矩形某条对角线上一点的 Y 坐标
 * @param x2        矩形同一条对角线上另一点的 X 坐标
 * @param y2        矩形同一条对角线上另一点的 Y 坐标
 */
void yage_rectangle_border(double x1, double y1, double x2, double y2);

/**
 * \~english @brief Draw border and fill a sector.
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the sector, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * \~chinese @brief 画扇形的边框并填充。
 * @param x           扇形圆心的 X 坐标
 * @param y           扇形圆心的 Y 坐标
 * @param r           扇形的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_sector(double x, double y, double r, double angle_begin, double angle_end);

/**
 * \~english @brief Fill a sector, don't draw border.
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the sector, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * \~chinese @brief 填充扇形，不要画边框。
 * @param x           扇形圆心的 X 坐标
 * @param y           扇形圆心的 Y 坐标
 * @param r           扇形的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_sector_fill(double x, double y, double r, double angle_begin, double angle_end);

/**
 * \~english @brief Draw border of a sector, don't fill.
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the sector, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * \~chinese @brief 画扇形的边框，不要填充。
 * @param x           扇形圆心的 X 坐标
 * @param y           扇形圆心的 Y 坐标
 * @param r           扇形的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_sector_border(double x, double y, double r, double angle_begin, double angle_end);

/**
 * \~english @brief Draw border of an arc.
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the arc, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * \~chinese @brief 画弧。
 * @param x           圆心的 X 坐标
 * @param y           圆心的 Y 坐标
 * @param r           弧的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_arc_border(double x, double y, double r, double angle_begin, double angle_end);

/**
 * \~english @brief Draw line.
 * @param x1        the X coordinate of a point
 * @param y1        the Y coordinate of the point
 * @param x2        the X coordinate of another point
 * @param y2        the Y coordinate of the point
 *
 * \~chinese @brief 画直线段。
 * @param x1        某点的 X 坐标
 * @param y1        此点的 Y 坐标
 * @param x2        另一点的 X 坐标
 * @param y2        另一点的 Y 坐标
 */
void yage_line_border(double x1, double y1, double x2, double y2);

/**
 * \~english @brief Format and print text at given position.
 * @param x           the X coordinate at the beginning of the text
 * @param y           the Y coordinate at the beginning of the text
 * @param[in] format  Output format, like printf()
 * @param[in] ...     Data to format and print
 *
 * \~chinese @brief 格式化并在指定位置打印文字。
 * @param x           文字起点的 X 坐标
 * @param y           文字起点的 Y 坐标
 * @param[in] format  输出格式，标准同 printf()
 * @param[in] ...     待格式化并输出的数据
 */
void yage_printf(double x, double y, const char *format, ...);


/**
 * \~english @brief Data type describing main types of message.
 * \~chinese @brief 描述消息的主要类型的数据类型。
 */
enum yage_message_type {
  YageNop = 0,  ///< \~english No information. Simply ignore messages of this type.
                ///< \~chinese 无信息。忽略此类消息即可
  YageKbd,      ///< \~english Keyboard message, such as pressing or releasing a key. Use `kbd` member to retrieve keyboard data
                ///< \~chinese 键盘消息，包括键盘的按下、释放。使用 `kbd` 成员来获取键盘数据
  YageMouse,    ///< \~english Mouse message, such as pressing or releasing a button, or moving the cursor. Use `mouse` member to retrieve mouse data
                ///< \~chinese 鼠标消息，包括按下或释放按键或移动光标。使用 `mouse` 成员来获取鼠标数据
  YageWindow    ///< \~english Window message, such as getting or losing focus. Use `window` member to retrieve window data
                ///< \~chinese 窗口消息，包括获得或丢失焦点。使用 `window` 成员来获取鼠标数据
};

/**
 * \~english @brief Data type describing types of mouse message.
 * \~chinese @brief 描述鼠标消息类型的数据类型。
 */
enum yage_message_mouse_type {
  YageMousePress = 1,   ///< \~english Some Mouse button is pressed
                        ///< \~chinese 鼠标的某按钮被按下
  YageMouseRelease,     ///< \~english Some Mouse button is released
                        ///< \~chinese 鼠标的某按钮被释放
  YageMouseMove         ///< \~english Cursor is moving
                        ///< \~chinese 鼠标光标在移动
};

/**
 * \~english @brief Data type describing types of window message.
 * \~chinese @brief 描述窗口消息类型的数据类型。
 */
enum yage_message_window_type {
  YageWindowEnter = 1,  ///< \~english Window gaines focus
                        ///< \~chinese 窗口获得焦点
  YageWindowLeave,      ///< \~english Window loses focus
                        ///< \~chinese 窗口失去焦点
  YageWindowDestroy,    ///< \~english Window has been destroyed
                        ///< \~chinese 窗口被销毁
  YageWindowResize      ///< \~english Window has been resized
                        ///< \~chinese 窗口大小改变
};

/**
 * \~english @brief Object describing all types of message.
 * \~chinese @brief 描述窗口消息的对象。
 */
struct yage_message_t {
  enum yage_message_type type;              ///< \~english @brief Main type of message
                                            ///< \~chinese @brief 消息的主要类型

  void *source;                             ///< \~english @brief Pointer to internal C++ Window object
                                            ///< \~chinese @brief 指向内部的 C++ 窗口对象的指针

  union {
    /**
     * \~english @brief Object describing keyboard message
     * \~chinese @brief 描述键盘消息的对象
     */
    struct {
      bool is_press;                        ///< \~english @brief Whether the key is pressed or released
                                            ///< \~chinese @brief 键是被按下还是被释放
      uint32_t keyval;                      ///< \~english @brief A character representing what will appear on a text box when you press current key, like 'a', 'b', ...
                                            ///< \~chinese @brief 表示键的字符，即当文本框中按下此键输出的内容，例如 'a', 'b', ...
      uint16_t keycode;                     ///< \~english @brief A number repersenting position of the physical key, like 38, 39, ...
                                            ///< \~chinese @brief 表示键在键盘上物理位置的数字，例如 38, 39, ...
      bool is_modkey    : 1;                ///< \~english @brief Whether the key is a modifier, like Ctrl / Alt / Shift
                                            ///< \~chinese @brief 键是否为控制键，例如 Ctrl / Alt / Shift
      bool modkey_alt   : 1;                ///< \~english @brief Whether Alt key is pressed
                                            ///< \~chinese @brief Alt 键是否被按下
      bool modkey_ctrl  : 1;                ///< \~english @brief Whether Ctrl key is pressed
                                            ///< \~chinese @brief Ctrl 键是否被按下
      bool modkey_shift : 1;                ///< \~english @brief Whether Shift key is pressed
                                            ///< \~chinese @brief Shift 键是否被按下
    } kbd;

    /**
     * \~english @brief Object describing mouse message
     * \~chinese @brief 描述鼠标消息的对象
     */
    struct {
      double x;                             ///< \~english @brief X coordinate of the cursor position
                                            ///< \~chinese @brief 光标的 X 坐标
      double y;                             ///< \~english @brief Y coordinate of the cursor position
                                            ///< \~chinese @brief 光标的 Y 坐标
      enum yage_message_mouse_type type;    ///< \~english @brief Type of mouse message
                                            ///< \~chinese @brief 鼠标消息的类型
      bool is_left      : 1;                ///< \~english @brief Whether the left button is pressed
                                            ///< \~chinese @brief 鼠标左键是否被按下
      bool is_right     : 1;                ///< \~english @brief Whether the right button is pressed
                                            ///< \~chinese @brief 鼠标右键是否被按下
      bool is_middle    : 1;                ///< \~english @brief Whether the middle button is pressed
                                            ///< \~chinese @brief 鼠标中键是否被按下
      bool modkey_alt   : 1;                ///< \~english @brief Whether Alt key is pressed
                                            ///< \~chinese @brief Alt 键是否被按下
      bool modkey_ctrl  : 1;                ///< \~english @brief Whether Ctrl key is pressed
                                            ///< \~chinese @brief Ctrl 键是否被按下
      bool modkey_shift : 1;                ///< \~english @brief Whether Shift key is pressed
                                            ///< \~chinese @brief Shift 键是否被按下
    } mouse;

    /**
     * \~english @brief Object describing window message
     * \~chinese @brief 描述窗口消息的对象
     */
    struct {
      enum yage_message_window_type type;   ///< \~english @brief Type of window message
                                            ///< \~chinese @brief 窗口消息的类型
    } window;
  };
};

/**
 * \~english @brief Get a message from message queue.
 * @param[out] msg  Return location to message
 * @param wait_ms   Maximium wait time if no message is available
 * @return          Whether the message queue is availiable.
 *                  When all windows are closed, the return value is `FALSE`
 *
 * \~chinese @brief 从消息队列中拉取一条消息。
 * @param[out] msg  消息的返回地址
 * @param wait_ms   队列中没有消息时，最长的等待时间
 * @return          消息队列是否可用。当全部窗口已经关闭时，返回值为 `FALSE`
 */
int  yage_get_message(struct yage_message_t *msg, int wait_ms);

/**
 * \~english @brief Wait until the next key press, and return the key value.
 * @return A character repersenting current key
 *
 * \~chinese @brief 等待下一次键盘输入，并返回键值。
 * @return 表示键值的字符
 */
int  yage_get_key(void);

/**
 * \~english @brief Show font chooser dialog and change font according to user input.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @return          Whether user changed font settings
 *
 * \~chinese @brief 显示字体选择对话框并根据用户输入修改字体。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @return          用户是否修改了字体设置
 */
int  yage_dlg_font(const char *title);

/**
 * \~english @brief Get color by showing a color chooser dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[out] color Return location of the color
 * @return          Whether the color is set
 *
 * \~chinese @brief 通过显示颜色选择对话框获得颜色对象。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[out] color 颜色对象的返回地址
 * @return          颜色对象是否被设置
 */
int  yage_dlg_color(const char *title, struct yage_color_t *color);

/**
 * \~english @brief Get path by showing a file save dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @return          Pointer to the path
 * \remark          Free returned pointer to path after use.
 *
 * \~chinese @brief 通过显示保存文件对话框获得文件路径。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @return          指向路径字符串的指针
 * \remark          在使用完毕后，释放返回的指针所指向的内存。
 */
char *yage_dlg_file_save(const char *title);

/**
 * \~english @brief Get path by showing a file open dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @return          Pointer to the path
 * \remark          Free returned pointer to path after use.
 *
 * \~chinese @brief 通过显示打开文件对话框获得文件路径。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @return          指向路径字符串的指针
 * \remark          在使用完毕后，释放返回的指针所指向的内存。
 */
char *yage_dlg_file_open(const char *title);

/**
 * \~english @brief Show a message dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 *
 * \~chinese @brief 显示消息对话框。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 */
void yage_dlg_message(const char *title, const char *message);

/**
 * \~english @brief Data type describing types of buttons in question dialog.
 * \~chinese @brief 描述询问对话框中按钮类型的数据类型。
 */
enum yage_dlg_button_t {
  kYageDlgButtonNone = 0,   ///< \~english No button
                            ///< \~chinese 无按钮
  kYageDlgButtonOk,         ///< \~english "OK" button
                            ///< \~chinese "确定" 按钮
  kYageDlgButtonClose,      ///< \~english "Close" button
                            ///< \~chinese "关闭" 按钮
  kYageDlgButtonCancel,     ///< \~english "Cancel" button
                            ///< \~chinese "取消" 按钮
  kYageDlgButtonYesNo,      ///< \~english "Yes" and "No" Button
                            ///< \~chinese "是" 和 "否" 按钮
  kYageDlgButtonOkCancel    ///< \~english "OK" and "Cancel" button
                            ///< \~chinese "确定" 和 "取消" 按钮
};

/**
 * \~english @brief Data type describing types of icons in question dialog.
 * \~chinese @brief 描述询问对话框中图标类型的数据类型。
 */
enum yage_dlg_icon_t {
  kYageDlgIconNone = 0,     ///< \~english No icon
                            ///< \~chinese 无图标
  kYageDlgIconInfo,         ///< \~english Information icon
                            ///< \~chinese 信息图标
  kYageDlgIconWarning,      ///< \~english Warning icon
                            ///< \~chinese 警告图标
  kYageDlgIconQuestion,     ///< \~english Question icon
                            ///< \~chinese 疑问图标
  kYageDlgIconError,        ///< \~english Error icon
                            ///< \~chinese 错误图标
};

/**
 * \~english @brief Data type describing types of user responses in question dialog.
 * \~chinese @brief 描述用户在询问对话框中的选择数据类型。
 */
enum yage_dlg_result_t {
  kYageDlgResultNone = 0,   ///< \~english No result
                            ///< \~chinese 无结果
  kYageDlgResultReject,     ///< \~english Reject button
                            ///< \~chinese "拒绝" 按钮
  kYageDlgResultAccept,     ///< \~english "Accept" button
                            ///< \~chinese "接受" 按钮
  kYageDlgResultOk,         ///< \~english "OK" button
                            ///< \~chinese "确定" 按钮
  kYageDlgResultCancel,     ///< \~english "Cancel" button
                            ///< \~chinese "取消" 按钮
  kYageDlgResultClose,      ///< \~english "Close" button
                            ///< \~chinese "关闭" 按钮
  kYageDlgResultYes,        ///< \~english "Yes" button
                            ///< \~chinese "是" 按钮
  kYageDlgResultNo,         ///< \~english "No" button
                            ///< \~chinese "否" 按钮
  kYageDlgResultApply,      ///< \~english "Apply" button
                            ///< \~chinese "应用" 按钮
  kYageDlgResultHelp,       ///< \~english "Help" button
                            ///< \~chinese "帮助" 按钮
};

/**
 * \~english @brief Show a question dialog and get user's response.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 * @param icon      Icon in the dialog
 * @param button    Combinations of buttons in dialog
 * @return          User's response
 *
 * \~chinese @brief 显示询问对话框，并读取用户的选择
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 * @param icon      对话框的图标
 * @param button    对话框的按钮
 * @return          用户的选择
 */
yage_dlg_result_t yage_dlg_question(const char *title,
                                    const char *message,
                                    yage_dlg_icon_t icon,
                                    yage_dlg_button_t button);

/**
 * \~english @brief Get an integer by showing a input dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 * @return          The integer input by user
 *
 * \~chinese @brief 通过显示输入对话框，获取一个整数。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 * @return          用户输入的整数
 */
int yage_input_int(const char *title, const char *message);

/**
 * \~english @brief Get a floating number by showing a input dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 * @return          The floating number input by user
 *
 * \~chinese @brief 通过显示输入对话框，获取一个浮点数。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 * @return          用户输入的浮点数
 */
double yage_input_double(const char *title, const char *message);

/**
 * \~english @brief Get user's input in input dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 * @return          Pointer to the string
 * \remark          Free returned pointer to path after use.
 *
 * \~chinese @brief 获取用户在输入对话框中的输入。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 * @return          指向用户输入内容的指针
 * \remark          在使用完毕后，释放返回的指针所指向的内存。
 */
char *yage_input_line(const char *title, const char *message);

/**
 * \~english @brief Get user's input in input dialog and convert the format.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 * @param[in] format Format to convert the data, like `scanf`
 * @param[out] ...  Location of data to write
 * @return          Number of variables written
 *
 * \~chinese @brief 获取并按照格式转换用户在输入对话框中的输入。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 * @param[in] format 转换的格式，如同 `scanf`
 * @param[out] ...  待写入的变量地址
 * @return          写入的变量数量
 */
int yage_input_scanf(const char *title, const char *message, const char *format, ...);

#ifdef __cplusplus
}  // extern "C"
#endif
#endif
