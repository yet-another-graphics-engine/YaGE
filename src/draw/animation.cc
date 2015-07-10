#include "animation.h"
#include "../util/encoding.h"

namespace yage {
namespace draw {

Animation::Animation(std::string filename) {
    GError *err = NULL;
    this->pixbuf_ = gdk_pixbuf_animation_new_from_file(filename.c_str(), &err);
    if (this->pixbuf_) {
        if (gdk_pixbuf_animation_is_static_image(this->pixbuf_)) {
            valid_ = false;
            fprintf(stderr, "This image is a static image, use yage_canvas instead.");
            g_object_unref(this->pixbuf_);
        } else {
            this->image_ = gtk_image_new_from_animation(pixbuf_);
            valid_ = true;
        }
    } else {
        valid_ = false;
        fprintf(stderr, "%s\n", err->message);
    }
}

Animation::~Animation() {
    if (valid_) {
        gtk_widget_destroy(GTK_WIDGET(this->image_));
        g_object_unref(this->pixbuf_);
    }
}

Animation::Animation(const Animation &animation) {
    if (animation.is_valid()) {
        pixbuf_ = animation.pro_get_pixbuf_animation();
        g_object_ref(pixbuf_);
        this->image_ = gtk_image_new_from_animation(pixbuf_);
        valid_ = true;
    } else {
        valid_ = false;
    }
}

bool Animation::is_valid(void) const {
    return valid_;
}

int Animation::get_width(void) const {
    if (valid_) {
        return gdk_pixbuf_animation_get_width(pixbuf_);
    } else {
        return -1;
    }
}

int Animation::get_height(void) const {
    if (valid_) {
        return gdk_pixbuf_animation_get_height(pixbuf_);
    } else {
        return -1;
    }
}

GdkPixbufAnimation *Animation::pro_get_pixbuf_animation() const {
    return pixbuf_;
}

GtkImage *Animation::pro_get_image() const {
    return GTK_IMAGE(image_);
}

}
}