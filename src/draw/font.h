#ifndef DRAW_FONT_H_
#define DRAW_FONT_H_
#include <pango/pango-font.h>
#include <string>

namespace yage {
namespace draw {

class Font {
private:
    PangoFontDescription *description_;
    static const char* yage_default_font_;
    #ifdef _WIN32
    static const char* get_win32_default_font_family();
    #endif // _WIN32
public:
    Font(const std::string &family = yage_default_font_, int size = 12, bool is_bold = false, bool is_italic = false);
    Font(Font &font);
    Font &operator=(Font &font);
    ~Font();

    #ifdef _WIN32
    static std::string get_win32_font_family_eng_name(const std::string& font_family);
    #endif // _WIN32

    static std::string get_font_family_yage_default();
    std::string get_font_family(void) const;
    int get_size(void) const;
    bool get_bold_status(void) const;
    bool get_italic_status(void) const;

    void set_font_family(const std::string &family);
    void set_size(int size);
    void set_bold_status(bool is_bold);
    void set_italic_status(bool is_italic);

    PangoFontDescription *pro_get_pango_font(void) const;
    void pro_set_pango_font(PangoFontDescription *description);
};


}
}


#endif //DRAW_FONT_H_
