#ifndef YAGE_ANIMATION_H
#define YAGE_ANIMATION_H
#include "../window/window.h"

namespace yage {
namespace draw {

/**
 * @brief yage::draw::Animation is a class to represent an image with animation,
 * such as a GIF image
 */
class Animation {
public:
    /**
     * @brief Create an Animation object using file specified by filename
     *
     * If we cannot find the file, or the image is not animated, the object
     * will be invalid, and the error message will be shown.
     * @param filename A string that contains the animated image's file name
     */
    Animation(std::string filename);


    /**
     * @brief Create an Animation object by copying exising Animation object
     */
    Animation(const Animation &animation);


    /**
     * @brief Delete the object
     *
     * It will also delete the widget on GtkWindow
     */
    ~Animation();

    /**
     * @brief Indicate that if the animation is valid
     * @return if the animation object is valid
     */
    bool is_valid(void) const;

    int get_width(void) const;
    int get_height(void) const;

    GdkPixbufAnimation *pro_get_pixbuf_animation(void) const;
    GtkImage *pro_get_image(void) const;

private:
    bool valid_;
    GdkPixbufAnimation *pixbuf_;
    GtkWidget *image_;
};

}
}

#endif //YAGE_ANIMATION_H
