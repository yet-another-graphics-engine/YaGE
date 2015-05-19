#ifndef YAGE_WIN32_H
#define YAGE_WIN32_H

namespace yage {
namespace util {

wchar_t *ansi_to_utf_16(const char *str);
char *utf_16_to_ansi(const wchar_t *wstr);
wchar_t *utf_8_to_utf_16(const char *str);
char *utf_16_to_utf_8(const wchar_t *wstr);
char *ansi_to_utf_8(const char *str);
char *utf_8_to_ansi(const char *wstr);

}
}

#endif //YAGE_WIN32_H
