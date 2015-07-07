#include "yage_button.h"

namespace yage {
    using namespace yage::api::yage;
    using yage::window::Message;

    Button::Button() {
        x_ = 0;
        y_ = 0;
        height_ = 0;
        width_ = 0;
        general_image_ = NULL;
        focused_image_ = NULL;
        clicked_image_ = NULL;
        is_focused_ = false;
        is_clicked_ = false;
    }
    Button::Button(int x, int y, int width, int height, Canvas &general_image, Canvas &focused_image, Canvas &clicked_image) {
        x_ = x;
        y_ = y;
        focused_image_ = NULL;
        clicked_image_ = NULL;
        general_image_ = new Canvas(general_image);
        focused_image_ = new Canvas(focused_image);
        clicked_image_ = new Canvas(clicked_image);
        height_ = height;
        width_ = width;
        is_focused_ = false;
        is_clicked_ = false;
    }

    Button::~Button() {
        if (general_image_) delete general_image_;
        if (focused_image_) delete focused_image_;
        if (clicked_image_) delete clicked_image_;
    }

    void Button::set_position(int x, int y) {
        x_ = x;
        y_ = y;
    }

    void Button::set_size(int height, int width) {
        height_ = height;
        width_ = width;

    }

    void Button::set_image(Canvas &image) {
        if (general_image_) delete general_image_;
        general_image_ = new Canvas(image);
    }

    void Button::set_focused_image(Canvas &image) {
        if (focused_image_) delete focused_image_;
        focused_image_ = new Canvas(image);
    }

    void Button::set_clicked_image(Canvas &image) {
        if (clicked_image_) delete clicked_image_;
        clicked_image_ = new Canvas(image);
    }

    bool Button::is_clicked(window::Message msg) {
        if (msg.type != msg.type_mouse) return false;
        if (msg.mouse.type == msg.mouse.type_move) {
            if (msg.mouse.x >= x_ && msg.mouse.x <= x_ + width_ &&
                msg.mouse.y >= y_ && msg.mouse.y <= y_ + height_) {
                if (!is_focused_) {
                    is_focused_ = true;
                    update_button();
                }
            } else {
                if (is_focused_) {
                    is_focused_ = false;
                    update_button();
                }
            }
        } else if (is_focused_ && msg.mouse.type == msg.mouse.type_press) {
            if (msg.mouse.is_left) {
                if (!is_clicked_) {
                    is_clicked_ = true;
                    update_button();
                }
            }
            return false;
        } else if (is_clicked_ && msg.mouse.type == msg.mouse.type_release) {
            if (msg.mouse.is_left) {
                is_clicked_ = false;
                update_button();
                if (is_focused_) return true;
            }
        }
        return false;
    }

    void Button::update_button() {
        Canvas *image = general_image_;
        if (is_focused_ && !is_clicked_ && focused_image_ != NULL)
            image = focused_image_;
        if (is_focused_ && is_clicked_ && clicked_image_ != NULL)
            image = clicked_image_;
        int raw_width, raw_height;
        double xscale = 1.0, yscale = 1.0;
        draw::Paint paint;
        general_image_->get_size(raw_width, raw_height);
        if (raw_width > 0 && width_ > 0) xscale = 1.0 * width_ / raw_width;
        if (raw_height > 0 && height_ > 0) yscale = 1.0 * height_ / raw_height;
        paint.set_scale(xscale, yscale);
        g_canvas_btn->draw_canvas(*image, draw::Point(x_ / xscale, y_ / yscale), paint);
        update();
    }

}

extern "C" {

struct yage_button *yage_button_create_empty(void) {
    yage::Button *button = new yage::Button();
    return reinterpret_cast<struct yage_button *>(button);
}

struct yage_button *yage_button_create(int x, int y, int width, int height,
                                       struct yage_canvas *general_image,
                                       struct yage_canvas *focused_image,
                                       struct yage_canvas *clicked_image) {
    draw::Canvas *general_canvas = reinterpret_cast<draw::Canvas *>(general_image);
    draw::Canvas *focused_canvas = reinterpret_cast<draw::Canvas *>(focused_image);
    draw::Canvas *clicked_canvas = reinterpret_cast<draw::Canvas *>(clicked_image);
    yage::Button *button = new yage::Button(x, y, width, height, *general_canvas, *focused_canvas, *clicked_canvas);
    return reinterpret_cast<struct yage_button *>(button);
}

void yage_button_delete(struct yage_button *button) {
    yage::Button *button_obj = reinterpret_cast<yage::Button *>(button);
    delete button_obj;
}

void yage_button_set_size(struct yage_button *button, int width, int height) {
    yage::Button *button_obj = reinterpret_cast<yage::Button *>(button);
    button_obj->set_size(width, height);
}

void yage_button_set_position(struct yage_button *button, int x, int y){
    yage::Button *button_obj = reinterpret_cast<yage::Button *>(button);
    button_obj->set_position(x,y);
}

void yage_button_set_image(struct yage_button *button, struct yage_canvas *general_image) {
    yage::Button *button_obj = reinterpret_cast<yage::Button *>(button);
    draw::Canvas *general_canvas = reinterpret_cast<draw::Canvas *>(general_image);
    button_obj->set_image(*general_canvas);
}

void yage_button_set_focused_image(struct yage_button *button, struct yage_canvas *focused_image) {
    yage::Button *button_obj = reinterpret_cast<yage::Button *>(button);
    draw::Canvas *focused_canvas = reinterpret_cast<draw::Canvas *>(focused_image);
    button_obj->set_focused_image(*focused_canvas);
}

void yage_button_set_clicked_image(struct yage_button *button, struct yage_canvas *clicked_image) {
    yage::Button *button_obj = reinterpret_cast<yage::Button *>(button);
    draw::Canvas *clicked_canvas = reinterpret_cast<draw::Canvas *>(clicked_image);
    button_obj->set_clicked_image(*clicked_canvas);
}

bool yage_button_clicked(struct yage_button *button, struct yage_message *msg) {
    window::Message *msg_obj = reinterpret_cast<window::Message *>(msg);
    yage::Button *button_obj = reinterpret_cast<yage::Button *>(button);
    return button_obj->is_clicked(*msg_obj);
}

void yage_button_update(struct yage_button *button) {
    yage::Button *button_obj = reinterpret_cast<yage::Button *>(button);
    button_obj->update_button();
}

}  // extern "C"