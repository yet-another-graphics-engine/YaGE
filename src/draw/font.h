#ifndef DRAW_FONT_H_
#define DRAW_FONT_H_
#include <pango/pango-font.h>
#include <string>

#ifdef _WIN32
#define YAGE_DEFAULT_FONT "Tahoma"
#elif defined(__APPLE__)
#if MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_9
#define YAGE_DEFAULT_FONT "Lucida Grande"
#else
#define YAGE_DEFAULT_FONT "Helvetica Neue"
#else
#define YAGE_DEFAULT_FONT "Sans Serif"
#endif

namespace yage {
namespace draw {

class Font {
private:
    PangoFontDescription *description_;
public:
    Font(std::string family = YAGE_DEFAULT_FONT, int size = 12, bool is_bold = false, bool is_italic = false);
	Font(Font &font);
    Font &operator=(Font &font);
    ~Font();

    std::string get_font_family(void) const;
    int get_size(void) const;
    bool get_bold_status(void) const;
    bool get_italic_status(void) const;

    void set_font_family(std::string family);
    void set_size(int size);
    void set_bold_status(bool is_bold);
    void set_italic_status(bool is_italic);

    PangoFontDescription *pro_get_pango_font(void);
    void pro_set_pango_font(PangoFontDescription *description);
};


}
}


#endif //DRAW_FONT_H_
