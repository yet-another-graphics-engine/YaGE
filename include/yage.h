﻿/**
 * @file yage.h
 * @brief @~english Declaration for exported YaGE API.
 *        @~chinese YaGE 的导出 API 声明。
 */
#ifndef YAGE_H_
#define YAGE_H_

#include "yage/common.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @~english
 * @defgroup draw_color Color
 * @brief Setting and using color.
 *
 * @~chinese
 * @defgroup draw_color 颜色
 * @brief 设置并使用颜色。
 */

/**
 * @~english
 * @defgroup system System
 * @brief Program level control.
 *
 * @~chinese
 * @defgroup system 系统
 * @brief 全程序级别的控制。
 */

/**
 * @~english
 * @defgroup draw Draw
 * @brief Draw shapes and images.
 *
 * @~chinese
 * @defgroup draw 绘图
 * @brief 绘制图形和图像。
 */

/**
 * @~english
 * @defgroup draw_shape Shape
 * @brief Draw a shape, with or without border and fill.
 * @ingroup draw
 *
 * @~chinese
 * @defgroup draw_shape 图形
 * @brief 画图形，可选填充或边框。
 * @ingroup draw
 */

/**
 * @~english
 * @defgroup draw_text Text
 * @brief Print text, with customizable fonts.
 * @ingroup draw
 *
 * @~chinese
 * @defgroup draw_text 文字
 * @brief 显示文字，可定制字体。
 * @ingroup draw
 */

/**
 * @~english
 * @defgroup draw_canvas Canvas
 * @brief A container for shapes and images.
 * @ingroup draw
 *
 * @~chinese
 * @defgroup draw_canvas 画布
 * @brief 图形和图像的容器。
 * @ingroup draw
 */

/**
 * @~english
 * @defgroup draw_canvas_shape Shape
 * @brief Draw a shape in canvas, with or without border and fill.
 * @ingroup draw_canvas
 *
 * @~chinese
 * @defgroup draw_canvas_shape 图形
 * @brief 在画布内画图形，可选填充或边框。
 * @ingroup draw_canvas
 */

/**
 * @~english
 * @defgroup draw_canvas_text Text
 * @brief Print text in canvas, with customizable fonts.
 * @ingroup draw_canvas
 *
 * @~chinese
 * @defgroup draw_canvas_text 文字
 * @brief 在画布内显示文字，可定制字体。
 * @ingroup draw_canvas
 */

/**
 * @~english
 * @defgroup draw_animation Animation
 * @brief A struct for representing animated image
 * @ingroup draw
 *
 * @~chinese
 * @defgroup draw_animation 动态图
 * @brief 用来表示动态图的结构体。
 * @ingroup draw
 */

/**
 * @~english
 * @defgroup interact Interaction
 * @brief Interact with user inputs.
 *
 * @~chinese
 * @defgroup interact 交互
 * @brief 与用户交互。
 */

/**
 * @~english
 * @defgroup interact_msg Message
 * @brief Messages representing events from keyboard, mouse and window.
 * @ingroup interact
 *
 * @~chinese
 * @defgroup interact_msg 消息
 * @brief 表示键盘、鼠标和窗口事件的消息。
 * @ingroup interact
 */

/**
 * @~english
 * @defgroup interact_dlg Dialog
 * @brief Dialogs show in front of main window for specefied interaction usage.
 * @ingroup interact
 *
 * @~chinese
 * @defgroup interact_dlg 对话框
 * @brief 在主窗口前显示的窗口，供特定的交互用途。
 * @ingroup interact
 */

/**
 * @~english
 * @defgroup interact_input Input
 * @brief Get string, number, or customized format from user's text input.
 * @ingroup interact
 *
 * @~chinese
 * @defgroup interact_input 输入
 * @brief 从用户输入的文本中读取字符串、数字，或是自定义格式的数据。
 * @ingroup interact
 */

/**
 * @~english
 * @brief An object holding color information.
 * @ingroup draw_color
 *
 * @~chinese
 * @brief 存储颜色信息的结构体。
 * @ingroup draw_color
 */
struct yage_color {
  double r; ///< @~english Red, range: 0.0 to 1.0
            ///< @~chinese 红色，区间为 0.0 至 1.0
  double g; ///< @~english Green, range: 0.0 to 1.0
            ///< @~chinese 绿色，区间为 0.0 至 1.0
  double b; ///< @~english Blue, range: 0.0 to 1.0
            ///< @~chinese 蓝色，区间为 0.0 至 1.0
  double a; ///< @~english Alpha, range: 0.0 (transparent) to 1.0 (nontransparent)
            ///< @~chinese 透明度，区间为 0.0（透明）至 1.0（不透明）
};

/**
 * @ingroup draw_color
 *
 * @~english
 * @brief Get yage_color from a string.
 * @param color_str a string, in English, descripting the color
 * @return a struct representing the color
 * @remark If no suitable color is found, black color is returned.
 *
 * @~chinese
 * @brief 通过字符串获得 yage_color 结构体。
 * @param color_str 描述颜色的英文字符串
 * @return 颜色信息结构体
 * @remark 如果没有找到合适的颜色信息，返回黑色。
 */
struct yage_color yage_color_from_string(const char *color_str);

/**
 * @ingroup system
 *
 * @~english
 * @brief Pause execution of current function for some duration.
 * @param second the duration, in seconds
 * @remark the minimum supported duration is 1/1000000(1e-6) second。
 *
 * @~chinese
 * @brief 一段时间内暂停当前函数的执行。
 * @param second 暂停的时长，以秒计算
 * @remark 最小支持的暂停时长为 1/1000000(1e-6) 秒。
 */
void yage_sleep(double second);

/**
 * @ingroup system
 *
 * @~english
 * @brief Initialize the drawing components and create a fix-sized window.
 * @param width  the width of the window to create
 * @param height the height of the window to create
 *
 * @~chinese
 * @brief 初始化绘图组件，并创建一个指定大小的窗口。
 * @param width  新窗口的宽度
 * @param height 新窗口的高度
 */
void yage_init(int width, int height);

/**
 * @ingroup system
 *
 * @~english
 * @brief Close all windows and quit program.
 *
 * @~chinese
 * @brief 关闭全部窗口并退出程序。
 */
void yage_quit(void);

/**
 * @ingroup draw_canvas
 *
 * @~english
 * @brief A struct representing a canvas.
 *
 * The struct is opaque, user can create
 * a canvas by yage_canvas_create() or yage_canvas_load_image() and free the
 * canvas by yage_canvas_delete().
 *
 * @~chinese
 * @brief 表示画布的结构体。
 *
 * 这是一个不包含细节的结构体。可以通过 yage_canvas_create() 或
 * yage_canvas_load_image() 创建一个画布，通过 yage_canvas_delete()
 * 来释放一个画布。
 */
struct yage_canvas;

/**
 * @ingroup draw_canvas
 *
 * @~english
 * @brief Create a fix-sized canvas.
 * @param width  the width of the canvas to create
 * @param height the height of the canvas to create
 * @return the new canvas
 *
 * @~chinese
 * @brief 创建一个固定大小的画布。
 * @param width  新画布的宽度
 * @param height 新画布的高度
 * @return 新创建的画布
 */
struct yage_canvas *yage_canvas_create(int width, int height);

/**
 * @ingroup draw_canvas
 *
 * @~english
 * @brief Create a canvas and set the content to the specified static image.
 * @param path the path to load the image
 * @return the new canvas
 * @remark Free the canvas by yage_canvas_delete() after use.
 * Use yage_animation_load_image() to create an animated image.
 *
 * @~chinese
 * @brief 创建一个新画布，并将其内容设置为一静态图片。
 * @param path 载入的图片路径
 * @return 新创建的画布
 * @remark 在使用完后通过 yage_canvas_delete() 删除画布。
 * 使用 yage_animation_load_image() 来创建动态图。
 */
struct yage_canvas *yage_canvas_load_image(const char *path);

/**
 * @ingroup draw_canvas
 *
 * @~english
 * @brief Free an unused canvas.
 * @param canvas The canvas to free
 *
 * @~chinese
 * @brief 删除不再使用的画布。
 * @param canvas 待删除的画布
 */
void yage_canvas_delete(struct yage_canvas *canvas);

/**
 * @ingroup draw_animation
 *
 * @~english
 * @brief A struct representing a animated image.
 *
 * The struct is opaque, user can create an animated image using
 * yage_animation_load_image(), and use yage_draw_animation() to draw it
 * on default window. At last, use yage_animation_delete() to destroy.
 *
 * @~chinese
 * @brief 表示动态图片的结构体。
 *
 * 这是一个不包含细节的结构体。可以通过 yage_animation_load_image() 或创建一个
 * 动态图，使用 yage_draw_animation() 将其画在屏幕上，最后通过 yage_canvas_delete()
 * 来释放动态图并从屏幕上移除。
 */
struct yage_animation;

/**
 * @ingroup draw_animation
 *
 * @~english
 * @brief Create an animated image using the content inside path.
 * @param path the path to load the image
 * @return the new animated image or NULL if failed
 * @remark Free the canvas by yage_animation_delete() after use.
 * Use yage_canvas_load_image() to create a static image.
 *
 * @~chinese
 * @brief 创建一个新动态图
 * @param path 载入的图片路径
 * @return 新创建的动态图，如果创建失败，返回 NULL
 * @remark 在使用完后通过 yage_animation_delete() 删除。
 * 使用 yage_canvas_load_image() 创建静态图片。
 */
struct yage_animation *yage_animation_load_image(const char *path);

/**
 * @ingroup draw_animation
 *
 * @~english
 * @brief Draw an animated image on screen at specified position.
 * @param animation  the source animated imag
 * @param x          the X coordinate for the top-left corner of the source animated image on screen
 * @param y          the Y coordinate for the top-left corner of the source animated image on screen
 *
 * @~chinese
 * @brief 在屏幕指定位置缩放并画出原始动态图的内容。
 * @param animation  原始动态图
 * @param x          原始画布左上角在屏幕上的 X 坐标
 * @param y          原始画布左上角在屏幕上的 Y 坐标
 */
void yage_draw_animation(struct yage_animation *animation, double x, double y);

/**
 * @ingroup draw_animation
 *
 * @~english
 * @brief Free an animated image that will not be used and
 * remove it from screen.
 * @param animation The animated image to free
 *
 * @~chinese
 * @brief 删除不再使用的动态图，并将其从屏幕上移除。
 * @param animation 待删除的动态图
 */
void yage_animation_delete(struct yage_animation *animation);

/**
 * @ingroup draw
 *
 * @~english
 * @brief Clean the screen.
 *
 * Fill the whole screen with background color.
 *
 * @~chinese
 * @brief 清空屏幕内容。
 *
 * 将整个屏幕填充为背景色。
 * \see yage_set_background_color
 */
void yage_clear(void);

/**
 * @ingroup draw_canvas
 *
 * @~english
 * @brief Clean the whole canvas.
 * @param canvas    the canvas to clear
 *
 * Set the whole canvas to transparent.
 * @param canvas    被清空的画布
 *
 * @~chinese
 * @brief 清空画布内容。
 *
 * 将整个画布设置为透明。
 */
void yage_canvas_clear(struct yage_canvas *canvas);

/**
 * @ingroup draw_canvas
 *
 * @~english
 * @brief Get the height and width of the canvas.
 * @param canvas the canvas to obtain information from
 * @param[out] height return location to the height of the canvas
 * @param[out] width  return location to the width of the canvas
 *
 * @~chinese
 * @brief 获取画布的宽度和高度。
 * @param canvas 需要获取信息的画布
 * @param[out] height 返回画布高度的地址
 * @param[out] width  返回画布宽度的地址
 */
void yage_canvas_get_size(struct yage_canvas *canvas, int *height, int *width);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw specified color to a pixel.
 * @param x       the X coordinate of the pixel
 * @param y       the Y coordinate of the pixel
 * @param color   the color to set
 *
 * @~chinese
 * @brief 在指定位置的像素上填充颜色。
 * @param x       像素的 X 坐标
 * @param y       像素的 Y 坐标
 * @param color   欲填充的颜色
 */
void yage_draw_pixel(double x, double y, struct yage_color color);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw specified color to a pixel on canvas.
 * @param canvas  the canvas to draw on
 * @param x       the X coordinate of the pixel
 * @param y       the Y coordinate of the pixel
 * @param color   the color to set
 *
 * @~chinese
 * @brief 在画布指定位置的像素上填充颜色。
 * @param canvas  被绘制的画布
 * @param x       像素的 X 坐标
 * @param y       像素的 Y 坐标
 * @param color   欲填充的颜色
 */
void yage_canvas_draw_pixel(struct yage_canvas *canvas,
                            double x, double y, struct yage_color color);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw source canvas on screen at specified position with given scale.
 * @param canvas  the source canvas
 * @param x       the X coordinate for the top-left corner of the source canvas on screen
 * @param y       the Y coordinate for the top-left corner of the source canvas on screen
 * @param xscale  scale for X coordinate
 * @param yscale  scale for Y coordinate
 *
 * @~chinese
 * @brief 在屏幕指定位置缩放并画出原始画布的内容。
 * @param canvas  原始画布
 * @param x       原始画布左上角在屏幕上的 X 坐标
 * @param y       原始画布左上角在屏幕上的 Y 坐标
 * @param xscale  X 坐标的缩放比例
 * @param yscale  Y 坐标的缩放比例
 */
void yage_draw_canvas(struct yage_canvas *canvas,
                      double x, double y, double xscale, double yscale);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw source canvas on screen at specified position with given scale.
 * @param dst     the source canvas
 * @param src     the destination canvas
 * @param x       the X coordinate for the top-left corner of the source canvas on destination canvas
 * @param y       the Y coordinate for the top-left corner of the source canvas on destination canvas
 * @param xscale  scale for X coordinate
 * @param yscale  scale for Y coordinate
 *
 * @~chinese
 * @brief 在目标画布指定位置缩放并画出原始画布的内容。
 * @param dst     目标画布
 * @param src     原始画布
 * @param x       原始画布左上角在目标画布上的 X 坐标
 * @param y       原始画布左上角在目标画布上的 Y 坐标
 * @param xscale  X 坐标的缩放比例
 * @param yscale  Y 坐标的缩放比例
 */
void yage_canvas_draw_canvas(struct yage_canvas *dst, struct yage_canvas *src,
                             double x, double y,
                             double xscale, double yscale);

/**
 * @ingroup draw_text
 *
 * @~english
 * @brief Set the font family, size and style of font.
 * @param family  The family of the font. Use NULL to skip this setting
 * @param size    The size of the font. Use a negative number to skip this setting
 * @param bold    Pass 0 for nonbold font, >0 for bold font, <0 to skip this setting
 * @param italic  Pass 0 for nonitalic font, >0 for italic font, <0 to skip this setting
 *
 * @~chinese
 * @brief 设置字体名称、大小和样式。
 * @param family  字体的名称。传入 NULL 以跳过本项设置
 * @param size    字体的大小。传入一个负数以跳过本项设置
 * @param bold    传入 0 关闭粗体， >0 打开粗体， <0 跳过本项设置
 * @param italic  传入 0 关闭斜体， >0 打开斜体， <0 跳过本项设置
 */
void yage_set_font(const char *family, int size, int bold, int italic);

/**
 * @ingroup draw_color
 *
 * @~english
 * @brief Set the fill color in shapes.
 * @param fill_color The new fill color
 * \see yage_set_border_color
 *
 * @~chinese
 * @brief 设置形状里填充的颜色。
 * @param fill_color 新的填充色
 * \see yage_set_border_color
 */
void yage_set_fill_color(struct yage_color fill_color);

/**
 * @ingroup draw_color
 *
 * @~english
 * @brief Set the font color.
 * @param font_color The new font color
 *
 * @~chinese
 * @brief 设置字体的颜色。
 * @param font_color 新的字体色
 */
void yage_set_font_color(struct yage_color font_color);

/**
 * @ingroup draw_color
 *
 * @~english
 * @brief Set the background color.
 * @param background_color The new background color
 * \see yage_clear
 *
 * @~chinese
 * @brief 设置背景色。
 * @param background_color 新的背景色
 * \see yage_clear
 *
 */
void yage_set_background_color(struct yage_color background_color);

/**
 * @ingroup draw_color
 *
 * @~english
 * @brief Set the border color of shapes.
 * @param border_color The new border color
 * \see yage_set_fill_color
 *
 * @~chinese
 * @brief 设置图形边框的颜色。
 * @param border_color 新的边框颜色
 * \see yage_set_fill_color
 */
void yage_set_border_color(struct yage_color border_color);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Set the border thickness of shapes.
 * @param thickness The new border thickness
 *
 * @~chinese
 * @brief 设置图形边框的粗细。
 * @param thickness 新的边框粗细
 */
void yage_set_border_thickness(double thickness);

/**
 * @ingroup system
 *
 * @~english
 * @brief Set the title of the window
 * @param[in] title Title of the window. Pass `NULL` to use default title
 *
 * @~chinese
 * @brief 设置窗口标题
 * @param[in] title 窗口的标题。传入 `NULL` 以使用默认标题
 */
void yage_set_title(const char *title);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw border and fill a circle.
 * @param x  the X coordinate of the center of the circle
 * @param y  the Y coordinate of the center of the circle
 * @param r  the radius of the circle
 *
 * @~chinese
 * @brief 画边框并填充圆。
 * @param x  圆心的 X 坐标
 * @param y  圆心的 Y 坐标
 * @param r  圆的半径
 */
void yage_circle(double x, double y, double r);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw border and fill a circle.
 * @param canvas  the canvas to draw on
 * @param x  the X coordinate of the center of the circle
 * @param y  the Y coordinate of the center of the circle
 * @param r  the radius of the circle
 *
 * @~chinese
 * @brief 画边框并填充圆。
 * @param canvas  被绘制的画布
 * @param x  圆心的 X 坐标
 * @param y  圆心的 Y 坐标
 * @param r  圆的半径
 */
void yage_canvas_circle(struct yage_canvas *canvas,
                        double x, double y, double r);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Fill a circle, don't draw border.
 * @param x  the X coordinate of the center of the circle
 * @param y  the Y coordinate of the center of the circle
 * @param r  the radius of the circle
 *
 * @~chinese
 * @brief 填充圆，不画边框。
 * @param x  圆心的 X 坐标
 * @param y  圆心的 Y 坐标
 * @param r  圆的半径
 */
void yage_circle_fill(double x, double y, double r);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Fill a circle, don't draw border.
 * @param canvas  the canvas to draw on
 * @param x  the X coordinate of the center of the circle
 * @param y  the Y coordinate of the center of the circle
 * @param r  the radius of the circle
 *
 * @~chinese
 * @brief 填充圆，不画边框。
 * @param canvas  被绘制的画布
 * @param x  圆心的 X 坐标
 * @param y  圆心的 Y 坐标
 * @param r  圆的半径
 */
void yage_canvas_circle_fill(struct yage_canvas *canvas,
                             double x, double y, double r);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw border of a circle, don't fill.
 * @param x  the X coordinate of the center of the circle
 * @param y  the Y coordinate of the center of the circle
 * @param r  the radius of the circle
 *
 * @~chinese
 * @brief 画圆的边框，不要填充。
 * @param x  圆心的 X 坐标
 * @param y  圆心的 Y 坐标
 * @param r  圆的半径
 */
void yage_circle_border(double x, double y, double r);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw border of a circle, don't fill.
 * @param canvas  the canvas to draw on
 * @param x  the X coordinate of the center of the circle
 * @param y  the Y coordinate of the center of the circle
 * @param r  the radius of the circle
 *
 * @~chinese
 * @brief 画圆的边框，不要填充。
 * @param canvas  被绘制的画布
 * @param x  圆心的 X 坐标
 * @param y  圆心的 Y 坐标
 * @param r  圆的半径
 */
void yage_canvas_circle_border(struct yage_canvas *canvas,
                               double x, double y, double r);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw border and fill an ellipse.
 * @param x         the X coordinate of the center of the ellipse
 * @param y         the Y coordinate of the center of the ellipse
 * @param radius_x  the X radius of the ellipse
 * @param radius_y  the Y radius of the ellipse
 *
 * @~chinese
 * @brief 画边框并填充椭圆。
 * @param x         椭圆圆心的 X 坐标
 * @param y         椭圆圆心的 Y 坐标
 * @param radius_x  椭圆的 X 轴半径坐标
 * @param radius_y  椭圆的 Y 轴半径坐标
 */
void yage_ellipse(double x, double y, double radius_x, double radius_y);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw border and fill an ellipse.
 * @param canvas    the canvas to draw on
 * @param x         the X coordinate of the center of the ellipse
 * @param y         the Y coordinate of the center of the ellipse
 * @param radius_x  the X radius of the ellipse
 * @param radius_y  the Y radius of the ellipse
 *
 * @~chinese
 * @brief 画边框并填充椭圆。
 * @param canvas    被绘制的画布
 * @param x         椭圆圆心的 X 坐标
 * @param y         椭圆圆心的 Y 坐标
 * @param radius_x  椭圆的 X 轴半径坐标
 * @param radius_y  椭圆的 Y 轴半径坐标
 */
void yage_canvas_ellipse(struct yage_canvas *canvas,
                         double x, double y,
                         double radius_x, double radius_y);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Fill an ellipse, don't draw border.
 * @param x         the X coordinate of the center of the ellipse
 * @param y         the Y coordinate of the center of the ellipse
 * @param radius_x  the X radius of the ellipse
 * @param radius_y  the Y radius of the ellipse
 *
 * @~chinese
 * @brief 填充椭圆，不画边框。
 * @param x         椭圆圆心的 X 坐标
 * @param y         椭圆圆心的 Y 坐标
 * @param radius_x  椭圆的 X 轴半径坐标
 * @param radius_y  椭圆的 Y 轴半径坐标
 */
void yage_ellipse_fill(double x, double y, double radius_x, double radius_y);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Fill an ellipse, don't draw border.
 * @param canvas    the canvas to draw on
 * @param x         the X coordinate of the center of the ellipse
 * @param y         the Y coordinate of the center of the ellipse
 * @param radius_x  the X radius of the ellipse
 * @param radius_y  the Y radius of the ellipse
 *
 * @~chinese
 * @brief 填充椭圆，不画边框。
 * @param canvas    被绘制的画布
 * @param x         椭圆圆心的 X 坐标
 * @param y         椭圆圆心的 Y 坐标
 * @param radius_x  椭圆的 X 轴半径坐标
 * @param radius_y  椭圆的 Y 轴半径坐标
 */
void yage_canvas_ellipse_fill(struct yage_canvas *canvas,
                              double x, double y,
                              double radius_x, double radius_y);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw border of an ellipse, don't fill.
 * @param x         the X coordinate of the center of the ellipse
 * @param y         the Y coordinate of the center of the ellipse
 * @param radius_x  the X radius of the ellipse
 * @param radius_y  the Y radius of the ellipse
 *
 * @~chinese
 * @brief 画椭圆边框，不要填充。
 * @param x         椭圆圆心的 X 坐标
 * @param y         椭圆圆心的 Y 坐标
 * @param radius_x  椭圆的 X 轴半径坐标
 * @param radius_y  椭圆的 Y 轴半径坐标
 */
void yage_ellipse_border(double x, double y, double radius_x, double radius_y);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw border of an ellipse, don't fill.
 * @param canvas    the canvas to draw on
 * @param x         the X coordinate of the center of the ellipse
 * @param y         the Y coordinate of the center of the ellipse
 * @param radius_x  the X radius of the ellipse
 * @param radius_y  the Y radius of the ellipse
 *
 * @~chinese
 * @brief 画椭圆边框，不要填充。
 * @param canvas    被绘制的画布
 * @param x         椭圆圆心的 X 坐标
 * @param y         椭圆圆心的 Y 坐标
 * @param radius_x  椭圆的 X 轴半径坐标
 * @param radius_y  椭圆的 Y 轴半径坐标
 */
void yage_canvas_ellipse_border(struct yage_canvas *canvas,
                                double x, double y,
                                double radius_x, double radius_y);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw border and fill a rectangle.
 * @param x1        the X coordinate of a point on one diagonal line.
 * @param y1        the Y coordinate of the point on one diagonal line.
 * @param x2        the X coordinate of another point on the same diagonal line.
 * @param y2        the Y coordinate of the point on the same diagonal line.
 *
 * @~chinese
 * @brief 画矩形的边框并填充。
 * @param x1        矩形某条对角线上一点的 X 坐标
 * @param y1        矩形某条对角线上一点的 Y 坐标
 * @param x2        矩形同一条对角线上另一点的 X 坐标
 * @param y2        矩形同一条对角线上另一点的 Y 坐标
 */
void yage_rectangle(double x1, double y1, double x2, double y2);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw border and fill a rectangle.
 * @param canvas    the canvas to draw on
 * @param x1        the X coordinate of a point on one diagonal line.
 * @param y1        the Y coordinate of the point on one diagonal line.
 * @param x2        the X coordinate of another point on the same diagonal line.
 * @param y2        the Y coordinate of the point on the same diagonal line.
 *
 * @~chinese
 * @brief 画矩形的边框并填充。
 * @param canvas    被绘制的画布
 * @param x1        矩形某条对角线上一点的 X 坐标
 * @param y1        矩形某条对角线上一点的 Y 坐标
 * @param x2        矩形同一条对角线上另一点的 X 坐标
 * @param y2        矩形同一条对角线上另一点的 Y 坐标
 */
void yage_canvas_rectangle(struct yage_canvas *canvas,
                           double x1, double y1, double x2, double y2);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Fill a rectangle, don't fill.
 * @param x1        the X coordinate of a point on one diagonal line.
 * @param y1        the Y coordinate of the point on one diagonal line.
 * @param x2        the X coordinate of another point on the same diagonal line.
 * @param y2        the Y coordinate of the point on the same diagonal line.
 *
 * @~chinese
 * @brief 填充矩形，不要画边框。
 * @param x1        矩形某条对角线上一点的 X 坐标
 * @param y1        矩形某条对角线上一点的 Y 坐标
 * @param x2        矩形同一条对角线上另一点的 X 坐标
 * @param y2        矩形同一条对角线上另一点的 Y 坐标
 */
void yage_rectangle_fill(double x1, double y1, double x2, double y2);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Fill a rectangle, don't fill.
 * @param canvas    the canvas to draw on
 * @param x1        the X coordinate of a point on one diagonal line.
 * @param y1        the Y coordinate of the point on one diagonal line.
 * @param x2        the X coordinate of another point on the same diagonal line.
 * @param y2        the Y coordinate of the point on the same diagonal line.
 *
 * @~chinese
 * @brief 填充矩形，不要画边框。
 * @param canvas    被绘制的画布
 * @param canvas    被绘制的画布
 * @param x1        矩形某条对角线上一点的 X 坐标
 * @param y1        矩形某条对角线上一点的 Y 坐标
 * @param x2        矩形同一条对角线上另一点的 X 坐标
 * @param y2        矩形同一条对角线上另一点的 Y 坐标
 */
void yage_canvas_rectangle_fill(struct yage_canvas *canvas,
                                double x1, double y1, double x2, double y2);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw border of a rectangle, don't fill.
 * @param x1        the X coordinate of a point on one diagonal line.
 * @param y1        the Y coordinate of the point on one diagonal line.
 * @param x2        the X coordinate of another point on the same diagonal line.
 * @param y2        the Y coordinate of the point on the same diagonal line.
 *
 * @~chinese
 * @brief 画矩形边框，不要填充。
 * @param x1        矩形某条对角线上一点的 X 坐标
 * @param y1        矩形某条对角线上一点的 Y 坐标
 * @param x2        矩形同一条对角线上另一点的 X 坐标
 * @param y2        矩形同一条对角线上另一点的 Y 坐标
 */
void yage_rectangle_border(double x1, double y1, double x2, double y2);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw border of a rectangle, don't fill.
 * @param canvas    the canvas to draw on
 * @param x1        the X coordinate of a point on one diagonal line.
 * @param y1        the Y coordinate of the point on one diagonal line.
 * @param x2        the X coordinate of another point on the same diagonal line.
 * @param y2        the Y coordinate of the point on the same diagonal line.
 *
 * @~chinese
 * @brief 画矩形边框，不要填充。
 * @param canvas    被绘制的画布
 * @param x1        矩形某条对角线上一点的 X 坐标
 * @param y1        矩形某条对角线上一点的 Y 坐标
 * @param x2        矩形同一条对角线上另一点的 X 坐标
 * @param y2        矩形同一条对角线上另一点的 Y 坐标
 */
void yage_canvas_rectangle_border(struct yage_canvas *canvas,
                                  double x1, double y1, double x2, double y2);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw border and fill a sector.
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the sector, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * @~chinese
 * @brief 画扇形的边框并填充。
 * @param x           扇形圆心的 X 坐标
 * @param y           扇形圆心的 Y 坐标
 * @param r           扇形的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_sector(double x, double y, double r, double angle_begin, double angle_end);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw border and fill a sector.
 * @param canvas    the canvas to draw on
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the sector, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * @~chinese
 * @brief 画扇形的边框并填充。
 * @param canvas    被绘制的画布
 * @param x           扇形圆心的 X 坐标
 * @param y           扇形圆心的 Y 坐标
 * @param r           扇形的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_canvas_sector(struct yage_canvas *canvas,
                        double x, double y, double r,
                        double angle_begin, double angle_end);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Fill a sector, don't draw border.
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the sector, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * @~chinese
 * @brief 填充扇形，不要画边框。
 * @param x           扇形圆心的 X 坐标
 * @param y           扇形圆心的 Y 坐标
 * @param r           扇形的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_sector_fill(double x, double y, double r, double angle_begin, double angle_end);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Fill a sector, don't draw border.
 * @param canvas      the canvas to draw on
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the sector, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * @~chinese
 * @brief 填充扇形，不要画边框。
 * @param canvas      被绘制的画布
 * @param x           扇形圆心的 X 坐标
 * @param y           扇形圆心的 Y 坐标
 * @param r           扇形的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_canvas_sector_fill(struct yage_canvas *canvas,
                             double x, double y, double r,
                             double angle_begin, double angle_end);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw border of a sector, don't fill.
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the sector, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * @~chinese
 * @brief 画扇形的边框，不要填充。
 * @param x           扇形圆心的 X 坐标
 * @param y           扇形圆心的 Y 坐标
 * @param r           扇形的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_sector_border(double x, double y, double r, double angle_begin, double angle_end);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw border of a sector, don't fill.
 * @param canvas      the canvas to draw on
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the sector, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * @~chinese
 * @brief 画扇形的边框，不要填充。
 * @param canvas      被绘制的画布
 * @param x           扇形圆心的 X 坐标
 * @param y           扇形圆心的 Y 坐标
 * @param r           扇形的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_canvas_sector_border(struct yage_canvas *canvas,
                               double x, double y, double r,
                               double angle_begin, double angle_end);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw border of an arc.
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the arc, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * @~chinese
 * @brief 画弧。
 * @param x           圆心的 X 坐标
 * @param y           圆心的 Y 坐标
 * @param r           弧的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_arc_border(double x, double y, double r, double angle_begin, double angle_end);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw border of an arc.
 * @param canvas      the canvas to draw on
 * @param x           the X coordinate of the center
 * @param y           the Y coordinate of the center
 * @param r           the radius of the sector
 * @param angle_begin the beginning angle of the arc, in radian
 * @param angle_end   the end angle of the sector, in radian
 *
 * @~chinese
 * @brief 画弧。
 * @param canvas      被绘制的画布
 * @param x           圆心的 X 坐标
 * @param y           圆心的 Y 坐标
 * @param r           弧的半径
 * @param angle_begin 圆心角的开始，弧度制
 * @param angle_end   圆心角的结束，弧度制
 */
void yage_canvas_arc_border(struct yage_canvas *canvas,
                            double x, double y, double r,
                            double angle_begin, double angle_end);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw line.
 * @param x1        the X coordinate of a point
 * @param y1        the Y coordinate of the point
 * @param x2        the X coordinate of another point
 * @param y2        the Y coordinate of the point
 *
 * @~chinese
 * @brief 画直线段。
 * @param x1        某点的 X 坐标
 * @param y1        此点的 Y 坐标
 * @param x2        另一点的 X 坐标
 * @param y2        另一点的 Y 坐标
 */
void yage_line_border(double x1, double y1, double x2, double y2);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw line.
 * @param canvas    the canvas to draw on
 * @param x1        the X coordinate of a point
 * @param y1        the Y coordinate of the point
 * @param x2        the X coordinate of another point
 * @param y2        the Y coordinate of the point
 *
 * @~chinese
 * @brief 画直线段。
 * @param canvas    被绘制的画布
 * @param x1        某点的 X 坐标
 * @param y1        此点的 Y 坐标
 * @param x2        另一点的 X 坐标
 * @param y2        另一点的 Y 坐标
 */
void yage_canvas_line_border(struct yage_canvas *canvas,
                             double x1, double y1, double x2, double y2);

/**
 * @ingroup draw_text
 *
 * @~english
 * @brief Format and print text at given position.
 * @param x           the X coordinate at the beginning of the text
 * @param y           the Y coordinate at the beginning of the text
 * @param[in] format  Output format, like printf()
 * @param[in] ...     Data to format and print
 *
 * @~chinese
 * @brief 格式化并在指定位置打印文字。
 * @param x           文字起点的 X 坐标
 * @param y           文字起点的 Y 坐标
 * @param[in] format  输出格式，标准同 printf()
 * @param[in] ...     待格式化并输出的数据
 */
void yage_printf(double x, double y, const char *format, ...);

/**
 * @ingroup draw_canvas_text
 *
 * @~english
 * @brief Format and print text at given position.
 * @param canvas      the canvas to draw on
 * @param x           the X coordinate at the beginning of the text
 * @param y           the Y coordinate at the beginning of the text
 * @param[in] format  Output format, like printf()
 * @param[in] ...     Data to format and print
 *
 * @~chinese
 * @brief 格式化并在指定位置打印文字。
 * @param canvas      被绘制的画布
 * @param x           文字起点的 X 坐标
 * @param y           文字起点的 Y 坐标
 * @param[in] format  输出格式，标准同 printf()
 * @param[in] ...     待格式化并输出的数据
 */
void yage_canvas_printf(struct yage_canvas *canvas,
                        double x, double y, const char *format, ...);

/**
 * @~english
 * @brief Data type describing main types of message.
 * @~chinese
 * @brief 描述消息的主要类型的数据类型。
 */
enum yage_message_type {
  kYageNop = 0,  ///< @~english No information. Simply ignore messages of this type.
                 ///< @~chinese 无信息。忽略此类消息即可
  kYageKbd,      ///< @~english Keyboard message, such as pressing or releasing a key. Use `kbd` member to retrieve keyboard data
                 ///< @~chinese 键盘消息，包括键盘的按下、释放。使用 `kbd` 成员来获取键盘数据
  kYageMouse,    ///< @~english Mouse message, such as pressing or releasing a button, or moving the cursor. Use `mouse` member to retrieve mouse data
                 ///< @~chinese 鼠标消息，包括按下或释放按键或移动光标。使用 `mouse` 成员来获取鼠标数据
  kYageWindow    ///< @~english Window message, such as getting or losing focus. Use `window` member to retrieve window data
                 ///< @~chinese 窗口消息，包括获得或丢失焦点。使用 `window` 成员来获取鼠标数据
};

/**
 * @ingroup interact_msg
 *
 * @~english
 * @brief Data type describing types of mouse message.
 *
 * @~chinese
 * @brief 描述鼠标消息类型的数据类型。
 */
enum yage_message_mouse_type {
  kYageMousePress = 1,   ///< @~english Some Mouse button is pressed
                         ///< @~chinese 鼠标的某按钮被按下
  kYageMouseRelease,     ///< @~english Some Mouse button is released
                         ///< @~chinese 鼠标的某按钮被释放
  kYageMouseMove         ///< @~english Cursor is moving
                         ///< @~chinese 鼠标光标在移动
};

/**
 * @ingroup interact_msg
 *
 * @~english
 * @brief Data type describing types of window message.
 *
 * @~chinese
 * @brief 描述窗口消息类型的数据类型。
 */
enum yage_message_window_type {
  kYageWindowEnter = 1,  ///< @~english Window gaines focus
                         ///< @~chinese 窗口获得焦点
  kYageWindowLeave,      ///< @~english Window loses focus
                         ///< @~chinese 窗口失去焦点
  kYageWindowDestroy,    ///< @~english Window has been destroyed
                         ///< @~chinese 窗口被销毁
  kYageWindowResize      ///< @~english Window has been resized
                         ///< @~chinese 窗口大小改变
};

/**
 * @ingroup interact_msg
 *
 * @~english
 * @brief Object describing all types of message.
 *
 * @~chinese
 * @brief 描述窗口消息的对象。
 */
struct yage_message {
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
      uint8_t is_press;                     ///< \~english @brief Whether the key is pressed or released
                                            ///< \~chinese @brief 键是被按下还是被释放
      uint32_t keyval;                      ///< \~english @brief A character representing what will appear on a text box when you press current key, like 'a', 'b', ...
                                            ///< \~chinese @brief 表示键的字符，即当文本框中按下此键输出的内容，例如 'a', 'b', ...
      uint16_t keycode;                     ///< \~english @brief A number repersenting position of the physical key, like 38, 39, ...
                                            ///< \~chinese @brief 表示键在键盘上物理位置的数字，例如 38, 39, ...
      uint8_t is_modkey    : 1;             ///< \~english @brief Whether the key is a modifier, like Ctrl / Alt / Shift
                                            ///< \~chinese @brief 键是否为控制键，例如 Ctrl / Alt / Shift
      uint8_t modkey_alt   : 1;             ///< \~english @brief Whether Alt key is pressed
                                            ///< \~chinese @brief Alt 键是否被按下
      uint8_t modkey_ctrl  : 1;             ///< \~english @brief Whether Ctrl key is pressed
                                            ///< \~chinese @brief Ctrl 键是否被按下
      uint8_t modkey_shift : 1;             ///< \~english @brief Whether Shift key is pressed
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
      uint8_t is_left      : 1;             ///< \~english @brief Whether the left button is pressed
                                            ///< \~chinese @brief 鼠标左键是否被按下
      uint8_t is_right     : 1;             ///< \~english @brief Whether the right button is pressed
                                            ///< \~chinese @brief 鼠标右键是否被按下
      uint8_t is_middle    : 1;             ///< \~english @brief Whether the middle button is pressed
                                            ///< \~chinese @brief 鼠标中键是否被按下
      uint8_t modkey_alt   : 1;             ///< \~english @brief Whether Alt key is pressed
                                            ///< \~chinese @brief Alt 键是否被按下
      uint8_t modkey_ctrl  : 1;             ///< \~english @brief Whether Ctrl key is pressed
                                            ///< \~chinese @brief Ctrl 键是否被按下
      uint8_t modkey_shift : 1;             ///< \~english @brief Whether Shift key is pressed
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
 * @ingroup interact_msg
 *
 * @~english
 * @brief Get a message from message queue.
 * @param[out] msg  Return location to message
 * @param wait_ms   Maximium wait time if no message is available
 * @return          Whether the message queue is availiable.
 *                  When all windows are closed, the return value is `FALSE`
 *
 * @~chinese
 * @brief 从消息队列中拉取一条消息。
 * @param[out] msg  消息的返回地址
 * @param wait_ms   队列中没有消息时，最长的等待时间
 * @return          消息队列是否可用。当全部窗口已经关闭时，返回值为 `FALSE`
 */
int  yage_get_message(struct yage_message *msg, int wait_ms);

/**
 * @ingroup interact_msg
 *
 * @~english
 * @brief Wait until the next key press, and return the key value.
 * @return A character repersenting current key
 *
 * @~chinese
 * @brief 等待下一次键盘输入，并返回键值。
 * @return 表示键值的字符
 */
int  yage_get_key(void);

/**
 * @ingroup interact_dlg
 *
 * @~english
 * @brief Show font chooser dialog and change font according to user input.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @return          Whether user changed font settings
 *
 * @~chinese
 * @brief 显示字体选择对话框并根据用户输入修改字体。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @return          用户是否修改了字体设置
 */
int  yage_dlg_font(const char *title);

/**
 * @ingroup interact_dlg
 *
 * @~english
 * @brief Get color by showing a color chooser dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[out] color Return location of the color
 * @return          Whether the color is set
 *
 * @~chinese
 * @brief 通过显示颜色选择对话框获得颜色对象。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[out] color 颜色对象的返回地址
 * @return          颜色对象是否被设置
 */
int  yage_dlg_color(const char *title, struct yage_color *color);

/**
 * @ingroup interact_dlg
 *
 * @~english
 * @brief Get path by showing a file save dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @return          Pointer to the path
 * @remark          Free returned pointer to path after use.
 *
 * @~chinese
 * @brief 通过显示保存文件对话框获得文件路径。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @return          指向路径字符串的指针
 * @remark          在使用完毕后，释放返回的指针所指向的内存。
 */
char *yage_dlg_file_save(const char *title);

/**
 * @ingroup interact_dlg
 *
 * @~english
 * @brief Get path by showing a file open dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @return          Pointer to the path
 * @remark          Free returned pointer to path after use.
 *
 * @~chinese
 * @brief 通过显示打开文件对话框获得文件路径。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @return          指向路径字符串的指针
 * @remark          在使用完毕后，释放返回的指针所指向的内存。
 */
char *yage_dlg_file_open(const char *title);

/**
 * @ingroup interact_dlg
 *
 * @~english
 * @brief Show a message dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 *
 * @~chinese
 * @brief 显示消息对话框。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 */
void yage_dlg_message(const char *title, const char *message);

/**
 * @ingroup interact_dlg
 *
 * @~english
 * @brief Data type describing types of buttons in question dialog.
 *
 * @~chinese
 * @brief 描述询问对话框中按钮类型的数据类型。
 */
enum yage_dlg_button_type {
  kYageDlgButtonNone = 0,   ///< @~english No button
                            ///< @~chinese 无按钮
  kYageDlgButtonOk,         ///< @~english "OK" button
                            ///< @~chinese "确定" 按钮
  kYageDlgButtonClose,      ///< @~english "Close" button
                            ///< @~chinese "关闭" 按钮
  kYageDlgButtonCancel,     ///< @~english "Cancel" button
                            ///< @~chinese "取消" 按钮
  kYageDlgButtonYesNo,      ///< @~english "Yes" and "No" Button
                            ///< @~chinese "是" 和 "否" 按钮
  kYageDlgButtonOkCancel    ///< @~english "OK" and "Cancel" button
                            ///< @~chinese "确定" 和 "取消" 按钮
};

/**
 * @ingroup interact_dlg
 *
 * @~english
 * @brief Data type describing types of icons in question dialog.
 *
 * @~chinese
 * @brief 描述询问对话框中图标类型的数据类型。
 */
enum yage_dlg_icon_type {
  kYageDlgIconNone = 0,     ///< @~english No icon
                            ///< @~chinese 无图标
  kYageDlgIconInfo,         ///< @~english Information icon
                            ///< @~chinese 信息图标
  kYageDlgIconWarning,      ///< @~english Warning icon
                            ///< @~chinese 警告图标
  kYageDlgIconQuestion,     ///< @~english Question icon
                            ///< @~chinese 疑问图标
  kYageDlgIconError,        ///< @~english Error icon
                            ///< @~chinese 错误图标
};

/**
 * @ingroup interact_dlg
 *
 * @~english
 * @brief Data type describing types of user responses in question dialog.
 *
 * @~chinese
 * @brief 描述用户在询问对话框中的选择数据类型。
 */
enum yage_dlg_result_type {
  kYageDlgResultNone = 0,   ///< @~english No result
                            ///< @~chinese 无结果
  kYageDlgResultReject,     ///< @~english Reject button
                            ///< @~chinese "拒绝" 按钮
  kYageDlgResultAccept,     ///< @~english "Accept" button
                            ///< @~chinese "接受" 按钮
  kYageDlgResultOk,         ///< @~english "OK" button
                            ///< @~chinese "确定" 按钮
  kYageDlgResultCancel,     ///< @~english "Cancel" button
                            ///< @~chinese "取消" 按钮
  kYageDlgResultClose,      ///< @~english "Close" button
                            ///< @~chinese "关闭" 按钮
  kYageDlgResultYes,        ///< @~english "Yes" button
                            ///< @~chinese "是" 按钮
  kYageDlgResultNo,         ///< @~english "No" button
                            ///< @~chinese "否" 按钮
  kYageDlgResultApply,      ///< @~english "Apply" button
                            ///< @~chinese "应用" 按钮
  kYageDlgResultHelp,       ///< @~english "Help" button
                            ///< @~chinese "帮助" 按钮
};

/**
 * @ingroup interact_dlg
 *
 * @~english
 * @brief Show a question dialog and get user's response.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 * @param icon      Icon in the dialog
 * @param button    Combinations of buttons in dialog
 * @return          User's response
 *
 * @~chinese
 * @brief 显示询问对话框，并读取用户的选择
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 * @param icon      对话框的图标
 * @param button    对话框的按钮
 * @return          用户的选择
 */
enum yage_dlg_result_type
yage_dlg_question(const char *title,
                  const char *message,
                  enum yage_dlg_icon_type icon,
                  enum yage_dlg_button_type button);

/**
 * @ingroup interact_input
 *
 * @~english
 * @brief Get an integer by showing a input dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 * @return          The integer input by user
 *
 * @~chinese
 * @brief 通过显示输入对话框，获取一个整数。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 * @return          用户输入的整数
 */
int yage_input_int(const char *title, const char *message);

/**
 * @ingroup interact_input
 *
 * @~english
 * @brief Get a floating number by showing a input dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 * @return          The floating number input by user
 *
 * @~chinese
 * @brief 通过显示输入对话框，获取一个浮点数。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 * @return          用户输入的浮点数
 */
double yage_input_double(const char *title, const char *message);

/**
 * @ingroup interact_input
 *
 * @~english
 * @brief Get user's input in input dialog.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 * @return          Pointer to the string
 * @remark          Free returned pointer to path after use.
 *
 * @~chinese
 * @brief 获取用户在输入对话框中的输入。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 * @return          指向用户输入内容的指针
 * @remark          在使用完毕后，释放返回的指针所指向的内存。
 */
char *yage_input_line(const char *title, const char *message);

/**
 * @ingroup interact_input
 *
 * @~english
 * @brief Get user's input in input dialog and convert the format.
 * @param[in] title Title of the dialog. Pass `NULL` to use default title
 * @param[in] message Content of the dialog. Pass `NULL` to use default content
 * @param[in] format Format to convert the data, like `scanf`
 * @param[out] ...  Location of data to write
 * @return          Number of variables written
 *
 * @~chinese
 * @brief 获取并按照格式转换用户在输入对话框中的输入。
 * @param[in] title 对话框的标题。传入 `NULL` 以使用默认标题
 * @param[in] message 对话框的内容。传入 `NULL` 以使用默认内容
 * @param[in] format 转换的格式，如同 `scanf`
 * @param[out] ...  待写入的变量地址
 * @return          写入的变量数量
 */
int yage_input_scanf(const char *title, const char *message, const char *format, ...);

/**
 * @ingroup interact_button
 *
 * @~english
 * @breif Create a new empty button
 * @return The new button
 *
 * @~chinese
 * @breif 创建一个新的空按钮
 * @return 新创建的按钮
 */
struct yage_button *yage_button_create_empty(void);

/**
 * @ingroup interact_button
 *
 * @~english
 * @breif Create a new button
 * @param x The X coordinate for the top-left corner of the button.
 * @param y The Y coordinate for the top-left corner of the button.
 * @param width The width of the button.
 * @param height The height of the button.
 * @param general_image The image displayed at the general time
 * @param focused_image The image displayed when the button is focused. Pass `NULL` to use gerenal image.
 * @param clicked_image The image displayed when the button is clicked. Pass `NULL` to use focused image.
 * @return The new button
 *
 * @~chinese
 * @breif 创建一个新按钮
 * @param x 按钮在画布上的 X 坐标
 * @param y 按钮在画布上的 Y 坐标
 * @param width 按钮的宽
 * @param height 按钮的高
 * @param general_image 按钮在一般状态显示的图像
 * @param focused_image 按钮在获得焦点时显示的图像，传入 `NULL` 以使用一般状态时的图像
 * @param clicked_image 按钮在按下时显示的图像，传入 `NULL` 以使用按钮获得焦点时显示的图像
 * @return 新创建的按钮
 */
struct yage_button *yage_button_create(int x, int y, int width, int height,
                                       struct yage_canvas *general_image,
                                       struct yage_canvas *focused_image,
                                       struct yage_canvas *clicked_image);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Free an unused button.
 * @param button The button to free
 *
 * @~chinese
 * @brief 删除不再使用的按钮。
 * @param canvas 待删除的按钮
 */
void yage_button_delete(struct yage_button *button);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Set the size of the button
 * @param button The button to set
 * @param width The width of the button.
 * @param height The height of the button.
 *
 * @~chinese
 * @brief 设置按钮的大小
 * @param button 要设置的按钮
 * @param width 按钮的宽
 * @param height 按钮的高
 */
void yage_button_set_size(struct yage_button *button, int width, int height);

/**
 * @ingroup interact_button
 *
 * @~english
 * @breif Set the position of the button
 * @param button The button to set
 * @param x The X coordinate for the top-left corner of the button.
 * @param y The Y coordinate for the top-left corner of the button.
 *
 * @~chinese
 * @brief 设置按钮的位置
 * @param button 要设置的按钮
 * @param x 按钮在画布上的 X 坐标
 * @param y 按钮在画布上的 Y 坐标
 */
void yage_button_set_position(struct yage_button *button, int x, int y);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Set the image displayed at the general time
 * @param button The button to set
 * @param general_image The image displayed at the general time
 *
 * @~chinese
 * @brief 设置按钮在一般状态显示的图像
 * @param button 要设置的按钮
 * @param general_image 按钮在一般状态显示的图像
 */
void yage_button_set_image(struct yage_button *button, struct yage_canvas *general_image);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Set the image displayed when the button is focused.
 * @param button The button to set
 * @param focused_image The image displayed when the button is focused. Pass `NULL` to use gerenal image.
 *
 * @~chinese
 * @brief 设置按钮在获得焦点时显示的图像
 * @param button 要设置的按钮
 * @param focused_image 按钮在获得焦点时显示的图像，传入 `NULL` 以使用一般状态时的图像
 */
void yage_button_set_focused_image(struct yage_button *button, struct yage_canvas *focused_image);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Set the image displayed when the button is clicked.
 * @param button The button to set
 * @param focused_image The image displayed when the button is focused. Pass `NULL` to use gerenal image.
 *
 * @~chinese
 * @brief 设置按钮在按下时显示的图像
 * @param button 要设置的按钮
 * @param clicked_image 按钮在按下时显示的图像，传入 `NULL` 以使用按钮获得焦点时显示的图像
 */
void yage_button_set_clicked_image(struct yage_button *button, struct yage_canvas *clicked_image);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Check whether the button is clicked from the message
 * @param button The button to be checked
 * @param msg The message from message queue.
 * @return Whether the button is clicked.
 *
 * @~chinese
 * @brief 从消息中检查按钮是否被按下
 * @param button 要检查的按钮
 * @param msg 从消息队列中获取的消息
 * @return 按钮是否被按下
 */
bool yage_button_clicked(struct yage_button *button, struct yage_message *msg);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Update the display status of the button
 * @param button The button to update
 *
 * @~chinese
 * @brief 更新按钮的显示状态
 * @param button 要更新的按钮
 */
void yage_button_update(struct yage_button *button);

#ifdef __cplusplus
}  // extern "C"
#endif
#endif
