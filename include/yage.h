/**
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
 * @defgroup system System
 * @brief Program level functions.
 *
 * @~chinese
 * @defgroup system 系统
 * @brief 全程序级别的功能。
 */

/**
 * @~english
 * @defgroup system_exec Execution
 * @brief Control program's initialization, execution, and exit.
 * @ingroup system
 *
 * @~chinese
 * @defgroup system_exec 执行
 * @brief 控制程序的初始化、执行和退出。
 * @ingroup system
 */

/**
 * @~english
 * @defgroup random Random
 * @brief Random number generator, etc.
 * @ingroup system
 *
 * @~chinese
 * @defgroup random 随机数
 * @brief 随机数生成等工具。
 * @ingroup system
 */

/**
 * @~english
 * @defgroup timer Timer
 * @brief Timer based on message.
 * @ingroup system
 *
 * @~chinese
 * @defgroup timer 计时器
 * @brief 基于消息的计时器。
 * @ingroup system
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
 * @defgroup draw_color Color
 * @brief Setting and using color.
 * @ingroup draw
 *
 * @~chinese
 * @defgroup draw_color 颜色
 * @brief 设置并使用颜色。
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
 * @defgroup music Music
 * @brief Play the music.
 *
 * @~chinese
 * @defgroup music 音乐
 * @brief 播放音乐。
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
 * @defgroup interact_button Button
 * @brief A convenient method for using image-based buttons.
 * @ingroup interact
 *
 * @~chinese
 * @defgroup interact_button 按钮
 * @brief 方便的贴图按钮。
 * @ingroup interact
 */

/**
 * @~english
 * @defgroup window Window
 * @brief Create, control and remove multi windows.
 *
 * @~chinese
 * @defgroup window 窗口
 * @brief 创建、控制并移除多窗口。
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
 * @ingroup system_exec
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
 * @ingroup draw
 *
 * @~english
 * @brief Set whether windows should automatically update when canvas changes.
 * @param mode automatically update or not
 * @remark Default behavior is automatically update on changes.
 *         For performance related drawing, disable auto update and call
 *         yage_draw_update() when everything on window is ready.
 *
 * @~chinese
 * @brief 设置当画布变动时，窗口是否自动更新。
 * @param mode 是否自动更新
 * @remark 默认行为是在变动时自动更新窗口。对于高性能绘图情况，禁用自动更新，当画布内容绘制完全时，调用 yage_draw_update() 。
 */
void yage_draw_set_auto_update(int mode);

/**
 * @ingroup draw
 *
 * @~english
 * @brief Update the default window manually.
 * @remark When auto update is disabled by yage_draw_set_auto_update(FALSE), calling this function updates the default window. When auto update is enabled (by default), there's no need to call this function.
 *
 * @~chinese
 * @brief 手动更新默认窗口。
 * @remark 当自动更新被 yage_draw_set_auto_update(FALSE) 所禁用时，调用本函数以更新默认窗口。当自动更新启用时（默认情况），不需要调用本函数。
 */
void yage_draw_update();

/**
 * @ingroup window
 *
 * @~english
 * @brief A struct representing a window.
 *
 * The struct is opaque, user can create
 * a window by yage_window_create() and remove the window by yage_window_delete().
 *
 * @~chinese
 * @brief 表示窗口的结构体。
 *
 * 这是一个不包含细节的结构体。可以通过 yage_window_create() 创建一个画布，通过 yage_window_delete() 来删除一个窗口。
 */
struct yage_window;

/**
 * @ingroup window
 *
 * @~english
 * @brief Create and show a fix-sized window.
 * @param width  the width of the window to create
 * @param height the height of the window to create
 * @return the new window
 * @remark All drawings will take on the default window. Call yage_window_set_default() to draw on another window.
 *
 * @~chinese
 * @brief 创建并显示一个新窗口。
 * @param width  新窗口的宽度
 * @param height 新窗口的高度
 * @return 新创建的窗口
 * @remark 全部的绘图都在默认窗口上进行。通过调用 yage_window_set_default() 在其他窗口上绘图。
 */
struct yage_window *yage_window_create(int width, int height);

/**
 * @ingroup window
 *
 * @~english
 * @brief Remove the default window.
 * @param new_default_window new default window after removal
 *
 * @~chinese
 * @brief 移除默认窗口。
 * @param new_default_window 移除后的默认窗口
 */
void yage_window_delete(struct yage_window *new_default_window);

/**
 * @ingroup window
 *
 * @~english
 * @brief Set the title of the window.
 * @param[in] title Title of the window. Pass `NULL` to use the default title
 *
 * @~chinese
 * @brief 设置窗口标题。
 * @param[in] title 窗口的标题。传入 `NULL` 以使用默认标题
 */
void yage_window_set_title(const char *title);

/**
 * @ingroup window
 *
 * @~english
 * @brief Set the default window.
 * @param default_window new default window
 *
 * @~chinese
 * @brief 设置默认窗口。
 * @param default_window 新的默认窗口
 */
void yage_window_set_default(struct yage_window *default_window);

/**
 * @ingroup system_exec
 *
 * @~english
 * @brief Initialize the drawing components and create a fix-sized default window.
 * @param width  the width of the window to create
 * @param height the height of the window to create
 * @return the new window
 * @attention This function should be called only once before calling any other YaGE functions. Calling another time will result in undefined behavior, including but not limited to destroying the whole universe.
 *
 * @~chinese
 * @brief 初始化绘图组件，并创建一个指定大小的默认窗口。
 * @param width  新窗口的宽度
 * @param height 新窗口的高度
 * @return 新创建的窗口
 * @attention 本函数应在调用任何 YaGE 函数前调用，并且只应被调用一次。多次调用将导致未定义的行为，包括但不限于毁灭整个宇宙。
 */
struct yage_window *yage_init(int width, int height);

/**
 * @ingroup system_exec
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
 * on the default window. At last, use yage_animation_delete() to destroy.
 *
 * @~chinese
 * @brief 表示动态图片的结构体。
 *
 * 这是一个不包含细节的结构体。可以通过 yage_animation_load_image() 或创建一个
 * 动态图，使用 yage_draw_animation() 将其画在窗口上，最后通过 yage_canvas_delete()
 * 来释放动态图并从窗口上移除。
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
 * @brief Draw an animated image on the default window at specified position.
 * @param animation  the source animated imag
 * @param x          the X coordinate for the top-left corner of the source animated image on the default window
 * @param y          the Y coordinate for the top-left corner of the source animated image on the default window
 *
 * @~chinese
 * @brief 在默认窗口指定位置画出原始动态图的内容。
 * @param animation  原始动态图
 * @param x          原始画布左上角在默认窗口上的 X 坐标
 * @param y          原始画布左上角在默认窗口上的 Y 坐标
 */
void yage_draw_animation(struct yage_animation *animation, double x, double y);

/**
 * @ingroup draw_animation
 *
 * @~english
 * @brief Free an animated image that will not be used and remove it from the default window.
 * @param animation The animated image to free
 *
 * @~chinese
 * @brief 删除不再使用的动态图，并将其从默认窗口上移除。
 * @param animation 待删除的动态图
 */
void yage_animation_delete(struct yage_animation *animation);

/**
 * @ingroup music
 *
 * @~english
 * @brief Music player struct
 *
 * The struct is opaque, user can create a player using
 * yage_player_load_music(), and use yage_player_play() to start playing,
 * pause via yage_player_pause(), stop via yage_player_stop().
 * Finally destroy player using yage_player_delete().
 *
 * @~chinese
 * @brief 音乐播放器结构体
 *
 * 这是一个不包含细节的结构体，使用 yage_player_load_music() 创建播放器对象，使用
 * yage_player_play() 开始播放，通过 yage_player_pause() 来暂停，最后通过
 * yage_player_stop() 停止播放，接着，使用 yage_player_delete() 销毁对象。
 */
struct yage_player;

/**
 * @ingroup music
 *
 * @~english
 * @brief Create a music player using the music file content inside path.
 * @param path the path to load the music
 * @return the new music player or NULL if failed
 *
 * @~chinese
 * @brief 创建一个新的音乐播放器
 * @param path 载入的音乐路径
 * @return 新创建的播放器，如果创建失败，返回 NULL
 */
struct yage_player *yage_player_load_music(const char *path);

/**
 * @ingroup music
 *
 * @~english
 * @brief Play the music in the player
 * @param player the player to play
 *
 * @~chinese
 * @brief 播放播放器中的音乐
 * @param player  播放器对象
 */
void yage_player_play(struct yage_player *player);

/**
 * @ingroup music
 *
 * @~english
 * @brief Pause the music in the player
 * @param player the player to pause
 *
 * @~chinese
 * @brief 暂停播放器中的音乐
 * @param player  播放器对象
 */
void yage_player_pause(struct yage_player *player);

/**
 * @ingroup music
 *
 * @~english
 * @brief Stop the music in the player
 * @param player the player to stop
 *
 * @~chinese
 * @brief 停止播放器中的音乐
 * @param player  播放器对象
 */
void yage_player_stop(struct yage_player *player);

/**
 * @ingroup music
 *
 * @~english
 * @brief Get if the player is playing music
 * @param player the player
 * @return 1 if playing, otherwise 0
 *
 * @~chinese
 * @brief 获取播放器是否在播放中
 * @param player  播放器对象
 * @return 如果正在播放中，返回 1，否则，返回 0
 */
uint8_t yage_player_get_status(struct yage_player *player);

/**
 * @ingroup music
 *
 * @~english
 * @brief Free an animated image that will no longer be used.
 * @param player The player to free
 *
 * @~chinese
 * @brief 删除不再使用的播放器。
 * @param player 待删除的播放器
 */
void yage_player_delete(struct yage_player *player);

/**
 * @ingroup draw
 *
 * @~english
 * @brief Clean the default window.
 *
 * Fill the whole the default window with background color.
 *
 * @~chinese
 * @brief 清空默认窗口内容。
 *
 * 将整个默认窗口填充为背景色。
 * \see yage_set_background_color
 */
void yage_clear(void);

/**
 * @ingroup draw_canvas
 *
 * @~english
 * @brief Clean the whole canvas.
 * @param canvas    the canvas to clear
 * @attention This function sets the whole canvas to transparent. To fill the canvas with background color, use yage_canvas_rectangle_fill().
 *
 * @~chinese
 * @brief 清空画布内容。
 * @param canvas    被清空的画布
 * @attention 本函数将整个画布设置为透明。如果需要填充为有背景颜色的画布，请使用 yage_canvas_rectangle_fill()。
 *
 */
void yage_canvas_clear(struct yage_canvas *canvas);

/**
 * @ingroup draw_canvas
 *
 * @~english
 * @brief Get the height and width of the canvas.
 * @param canvas the canvas to obtain information from
 * @param[out] width  return location to the width of the canvas
 * @param[out] height return location to the height of the canvas
 *
 * @~chinese
 * @brief 获取画布的宽度和高度。
 * @param canvas 需要获取信息的画布
 * @param[out] width  返回画布宽度的地址
 * @param[out] height 返回画布高度的地址
 */
void yage_canvas_get_size(struct yage_canvas *canvas, int *width, int *height);

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
 * @brief Draw source canvas on the default window at specified position with given scale.
 * @param canvas  the source canvas
 * @param x       the X coordinate for the top-left corner of the source canvas on the default window
 * @param y       the Y coordinate for the top-left corner of the source canvas on the default window
 * @param xscale  scale for X coordinate
 * @param yscale  scale for Y coordinate
 *
 * @~chinese
 * @brief 在默认窗口指定位置缩放并画出原始画布的内容。
 * @param canvas  原始画布
 * @param x       原始画布左上角在默认窗口上的 X 坐标
 * @param y       原始画布左上角在默认窗口上的 Y 坐标
 * @param xscale  X 坐标的缩放比例
 * @param yscale  Y 坐标的缩放比例
 */
void yage_draw_canvas(struct yage_canvas *canvas,
                      double x, double y, double xscale, double yscale);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw source canvas on the default window at specified position with given scale.
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
 * @brief Draw border and fill a polygon.
 * @param num_points the number of vertexes of the polygon
 * @param poly_points the coordinates of each vertex, like `{X1, Y1, X2, Y2, X3, Y3, ...}`, number of elements counts to 2 * num_points
 *
 * @~chinese
 * @brief 画多边形的边框并填充。
 * @param num_points 多边形顶点数量
 * @param poly_points 多边形的顶点坐标，类似于 `{X1, Y1, X2, Y2, X3, Y3, ...}`，共 2 * num_points 个元素
 */
void yage_poly(int num_points, const double *poly_points);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw border and fill a polygon.
 * @param canvas    the canvas to draw on
 * @param num_points the number of vertexes of the polygon
 * @param poly_points the coordinates of each vertex, like `{X1, Y1, X2, Y2, X3, Y3, ...}`, number of elements counts to 2 * num_points
 *
 * @~chinese
 * @brief 画多边形的边框并填充。
 * @param canvas    被绘制的画布
 * @param num_points 多边形顶点数量
 * @param poly_points 多边形的顶点坐标，类似于 `{X1, Y1, X2, Y2, X3, Y3, ...}`，共 2 * num_points 个元素
 */
void yage_canvas_poly(struct yage_canvas *canvas,
                      int num_points, const double *poly_points);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Fill a polygon, don't fill.
 * @param num_points the number of vertexes of the polygon
 * @param poly_points the coordinates of each vertex, like `{X1, Y1, X2, Y2, X3, Y3, ...}`, number of elements counts to 2 * num_points
 *
 * @~chinese
 * @brief 填充多边形，不要画边框。
 * @param num_points 多边形顶点数量
 * @param poly_points 多边形的顶点坐标，类似于 `{X1, Y1, X2, Y2, X3, Y3, ...}`，共 2 * num_points 个元素
 */
void yage_poly_fill(int num_points, const double *poly_points);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Fill a polygon, don't fill.
 * @param canvas    the canvas to draw on
 * @param num_points the number of vertexes of the polygon
 * @param poly_points the coordinates of each vertex, like `{X1, Y1, X2, Y2, X3, Y3, ...}`, number of elements counts to 2 * num_points
 *
 * @~chinese
 * @brief 填充多边形，不要画边框。
 * @param canvas    被绘制的画布
 * @param num_points 多边形顶点数量
 * @param poly_points 多边形的顶点坐标，类似于 `{X1, Y1, X2, Y2, X3, Y3, ...}`，共 2 * num_points 个元素
 */
void yage_canvas_poly_fill(struct yage_canvas *canvas,
                           int num_points, const double *poly_points);

/**
 * @ingroup draw_shape
 *
 * @~english
 * @brief Draw border of a polygon, don't fill.
 * @param num_points the number of vertexes of the polygon
 * @param poly_points the coordinates of each vertex, like `{X1, Y1, X2, Y2, X3, Y3, ...}`, number of elements counts to 2 * num_points
 *
 * @~chinese
 * @brief 画多边形边框，不要填充。
 * @param num_points 多边形顶点数量
 * @param poly_points 多边形的顶点坐标，类似于 `{X1, Y1, X2, Y2, X3, Y3, ...}`，共 2 * num_points 个元素
 */
void yage_poly_border(int num_points, const double *poly_points);

/**
 * @ingroup draw_canvas_shape
 *
 * @~english
 * @brief Draw border of a polygon, don't fill.
 * @param canvas    the canvas to draw on
 * @param num_points the number of vertexes of the polygon
 * @param poly_points the coordinates of each vertex, like `{X1, Y1, X2, Y2, X3, Y3, ...}`, number of elements counts to 2 * num_points
 *
 * @~chinese
 * @brief 画多边形边框，不要填充。
 * @param canvas    被绘制的画布
 * @param num_points 多边形顶点数量
 * @param poly_points 多边形的顶点坐标，类似于 `{X1, Y1, X2, Y2, X3, Y3, ...}`，共 2 * num_points 个元素
 */
void yage_canvas_poly_border(struct yage_canvas *canvas,
                             int num_points, const double *poly_points);

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
  kYageWindow,    ///< @~english Window message, such as getting or losing focus. Use `window` member to retrieve window data
                 ///< @~chinese 窗口消息，包括获得或丢失焦点。使用 `window` 成员来获取鼠标数据
  kYageTimer
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
 * @brief Data type describing types of timer message.
 *
 * @~chinese
 * @brief 描述计时器消息类型的数据类型。
 */
enum yage_message_timer_type {
  kYageTimerRunning = 1, ///< @~english The timer is running
                         ///< @~chinese 计时器正在运行
  kYageTimerFinished     ///< @~english The timer has finished its job
                         ///< @~chinese 计时器已经结束任务
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

    /**
     * \~english @brief Object describing timer message
     * \~chinese @brief 描述计时器消息的对象
     */
    struct {
      struct yage_timer *timer;             ///< \~english @brief Pointer of timer structure
                                            ///< \~chinese @brief 指向计时器结构体的指针
      yage_message_timer_type type;         ///< \~english @brief Type of timer message
                                            ///< \~chinese @brief 计时器消息类型
      double seconds;                       ///< \~english @brief Seconds passed when the timer is active
                                            ///< \~chinese @brief 计时器处于激活状态时经过的秒数
    } timer;
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
 * @param[in] title Title of the dialog. Pass `NULL` to use the default title
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
 * @param[in] title Title of the dialog. Pass `NULL` to use the default title
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
 * @param[in] title Title of the dialog. Pass `NULL` to use the default title
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
 * @param[in] title Title of the dialog. Pass `NULL` to use the default title
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
 * @param[in] title Title of the dialog. Pass `NULL` to use the default title
 * @param[in] message Content of the dialog. Pass `NULL` to use the default content
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
 * @param[in] title Title of the dialog. Pass `NULL` to use the default title
 * @param[in] message Content of the dialog. Pass `NULL` to use the default content
 * @param icon      Icon in the dialog
 * @param button    Combinations of buttons in dialog
 * @return          User's response
 *
 * @~chinese
 * @brief 显示询问对话框，并读取用户的选择。
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
 * @param[in] title Title of the dialog. Pass `NULL` to use the default title
 * @param[in] message Content of the dialog. Pass `NULL` to use the default content
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
 * @param[in] title Title of the dialog. Pass `NULL` to use the default title
 * @param[in] message Content of the dialog. Pass `NULL` to use the default content
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
 * @param[in] title Title of the dialog. Pass `NULL` to use the default title
 * @param[in] message Content of the dialog. Pass `NULL` to use the default content
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
 * @param[in] title Title of the dialog. Pass `NULL` to use the default title
 * @param[in] message Content of the dialog. Pass `NULL` to use the default content
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
 * @brief Create a new empty button
 * @return The new button
 *
 * @~chinese
 * @brief 创建一个新的空按钮
 * @return 新创建的按钮
 */
struct yage_button *yage_button_create_empty(void);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Create a new button.
 * @param x The X coordinate for the top-left corner of the button
 * @param y The Y coordinate for the top-left corner of the button
 * @param width The width of the button
 * @param height The height of the button
 * @param general_image The image displayed at the general time
 * @param focused_image The image displayed when the button is focused. Pass `NULL` to use gerenal image
 * @param clicked_image The image displayed when the button is clicked. Pass `NULL` to use focused image
 * @return The new button
 *
 * @~chinese
 * @brief 创建一个新按钮。
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
 * @param button 待删除的按钮
 */
void yage_button_delete(struct yage_button *button);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Set the size of the button.
 * @param button The button to set
 * @param width The width of the button
 * @param height The height of the button
 *
 * @~chinese
 * @brief 设置按钮的大小。
 * @param button 要设置的按钮
 * @param width 按钮的宽
 * @param height 按钮的高
 */
void yage_button_set_size(struct yage_button *button, int width, int height);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Set the position of the button.
 * @param button The button to set
 * @param x The X coordinate for the top-left corner of the button.
 * @param y The Y coordinate for the top-left corner of the button.
 *
 * @~chinese
 * @brief 设置按钮的位置。
 * @param button 要设置的按钮
 * @param x 按钮在画布上的 X 坐标
 * @param y 按钮在画布上的 Y 坐标
 */
void yage_button_set_position(struct yage_button *button, int x, int y);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Set the image displayed at the general time.
 * @param button The button to set
 * @param general_image The image displayed at the general time
 *
 * @~chinese
 * @brief 设置按钮在一般状态显示的图像。
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
 * @param focused_image The image displayed when the button is focused. Pass `NULL` to use gerenal image
 *
 * @~chinese
 * @brief 设置按钮在获得焦点时显示的图像。
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
 * @param clicked_image The image displayed when the button is clicked. Pass `NULL` to use gerenal image
 *
 * @~chinese
 * @brief 设置按钮在按下时显示的图像。
 * @param button 要设置的按钮
 * @param clicked_image 按钮在按下时显示的图像，传入 `NULL` 以使用按钮获得焦点时显示的图像
 */
void yage_button_set_clicked_image(struct yage_button *button, struct yage_canvas *clicked_image);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Check whether the button is clicked from the message.
 * @param button The button to be checked
 * @param msg The message from message queue
 * @return Whether the button is clicked
 *
 * @~chinese
 * @brief 从消息中检查按钮是否被按下。
 * @param button 要检查的按钮
 * @param msg 从消息队列中获取的消息
 * @return 按钮是否被按下
 */
int yage_button_clicked(struct yage_button *button, struct yage_message *msg);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Update the display status of the button.
 * @param button The button to update
 * @return Whether the button is clicked.
 * @remark Button should be update manually after changed the properties
 *
 * @~chinese
 * @brief 更新按钮的显示状态。
 * @param button 要更新的按钮
 * @return 按钮是否被按下
 * @remark 按钮在修改属性后需要进行手动更新。
 */
void yage_button_update(struct yage_button *button);

/**
 * @ingroup interact_button
 *
 * @~english
 * @brief Set the visibility of the button.
 * @param button The button to set
 * @param is_visible The visibility of the button. 0 means it's invisible, 1 means it's visible
 * @remark The button will not be clicked when it's invisible.
 *
 * @~chinese
 * @brief 设置按钮的可见性。
 * @param button 要设置的按钮
 * @param is_visible 按钮的可见性，0 表示不可见，1 表示可见
 * @remark 按钮在不可见状态时不会被按下。
 */
void yage_button_set_visibility(struct yage_button *button, int is_visible);

/**
 * @ingroup random
 *
 * @~english
 * @brief Generate a random integer in [ begin, end )
 * @param begin The lower endpoint of the interval
 * @param end The upper endpoint of the interval
 * @return A random integer in [ begin, end )
 *
 * @~chinese
 * @brief 生成一个在 [ begin, end ) 中的随机整数。
 * @param begin 区间的下边界
 * @param end 区间的上边界
 * @return 在 [ begin, end ) 中的随机整数
 */
int yage_random_interval(int begin, int end);

/**
 * @ingroup random
 *
 * @~english
 * @brief Generate a random real number between 0 and 1
 * @return A random real number between 0 and 1
 *
 * @~chinese
 * @brief 生成一个 0 到 1 之间的随机实数
 * @return 一个 0 到 1 之间的随机实数
 */
double yage_random_double();

/**
 * @ingroup timer
 *
 * @~english
 * @brief Create a timer
 * @param seconds Time for timer to wait. If you specify a number greater than
 * 0, the timer will run until `seconds` seconds. Otherwise, if you specify a
 * number less than or equal to 0, the timer will run forever.
 * @return A timer created
 * @remark The timer will send you message every 0.02 second since created with
 * timer type `kYageTimerRunning`, at last, it will send you a message with
 * timer type `kYageTimerFinished`.
 *
 * @~chinese
 * @brief 创建计时器
 * @param seconds 要求计时器等待的时间。如果你指定了一个大于 0 的数字，计时器就会运行
 * `seconds` 秒，否则计时器会永远运行。
 * @return 新创建的计时器
 * @remark 计时器会每隔 0.02 秒向您发送计时器消息类型为 `kYageTimerRunning` 的消息，
 * 在计时结束时，它将会给您发送计时器消息类型为 `kYageTimerFinished` 的消息。
 */
struct yage_timer *yage_timer_create(double seconds);

/**
 * @ingroup timer
 *
 * @~english
 * @brief Get time that timer elapsed when it is active
 * @param timer The timer to get time
 * @return Seconds passed since timer is active
 *
 * @~chinese
 * @brief 获取计时器实时时间
 * @param timer 要获取时间的计时器
 * @return 计时器实时时间，单位为秒
 */
double yage_timer_get_time_elapsed(struct yage_timer *timer);

/**
 * @ingroup timer
 *
 * @~english
 * @brief Pause a timer
 * @param timer The timer to pause
 * @remark The timer will not send message to you since it has paused
 *
 * @~chinese
 * @brief 暂停计时器
 * @param timer 要暂停的计时器
 * @remark 计时器在暂停时将不会再向您发送消息
 */
void yage_timer_pause(struct yage_timer *timer);

/**
 * @ingroup timer
 *
 * @~english
 * @brief Resume a timer
 * @param timer The timer to resume
 * @remark We will send messages to you after resumed
 *
 * @~chinese
 * @brief 继续运行计时器
 * @param timer 要继续的计时器
 * @remark 在计时器继续运行时，我们会向您发送消息
 */
void yage_timer_resume(struct yage_timer *timer);

/**
 * @ingroup timer
 *
 * @~english
 * @brief Stop a timer
 * @param timer The timer to stop
 * @remark The timer will be reset with time 0, and paused
 *
 * @~chinese
 * @brief 停止计时器
 * @param timer 要停止的计时器
 * @remark 计时器的时间将被置 0，同时将会被暂停
 */
void yage_timer_stop(struct yage_timer *timer);

/**
 * @ingroup timer
 *
 * @~english
 * @brief Destroy the timer
 * @param timer The timer to destroy
 *
 * @~chinese
 * @brief 销毁计时器
 * @param timer 要销毁的计时器
 */
void yage_timer_delete(struct yage_timer *timer);

#ifdef __cplusplus
}  // extern "C"
#endif
#endif
