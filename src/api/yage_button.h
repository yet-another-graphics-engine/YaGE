#ifndef Button_H
#define Button_H

#include "yage.h"

namespace yage {

class Button {
private:
    int x_;
    int y_;
    int width_;
    int height_;
    Canvas *general_image_;
    Canvas *focused_image_;
    Canvas *clicked_image_;
    bool is_focused_;
    bool is_clicked_;
    bool is_updated_;
    yage::draw::Paint priv_btn_;
    bool is_visible_;

public:
    Button();
    Button(int x, int y, int width, int height, Canvas &general_image, Canvas &focused_image, Canvas &clicked_image);
    ~Button();
    void set_position(int x, int y);
    void set_size(int height, int width);
    void set_image(Canvas &image);
    void set_focused_image(Canvas &image);
    void set_clicked_image(Canvas &image);
    bool is_clicked(window::Message msg);
    void update_button();
    void set_visibility(bool visible);
};

}

#endif