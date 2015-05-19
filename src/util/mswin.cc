#include "mswin.h"
#include <windows.h>

namespace yage {
namespace util {

// use free()
wchar_t *ansi_to_utf_16(const char* str) {
	int length;
	wchar_t * result;
	length = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	result = (wchar_t *)malloc((length + 1)*sizeof(wchar_t));
	memset(result, 0, (length + 1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, str, -1, result, length);
	return result;
}

// use free()
char *utf_16_to_ansi(const wchar_t *wstr) {
	char *result;
	int length;
	length = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	result = (char *)malloc((length + 1)*sizeof(char));
	memset(result, 0, sizeof(char) * (length + 1));
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, result, length, NULL, NULL);
	return result;
}

// use free()
wchar_t *utf_8_to_utf_16(const char* str) {
	int length;
	wchar_t * result;
	length = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	result = (wchar_t *)malloc((length + 1)*sizeof(wchar_t));
	memset(result, 0, (length + 1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, result, length);
	return result;
}

// use free()
char *utf_16_to_utf_8(const wchar_t *wstr) {
	char *result;
	int length;
	length = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	result = (char *)malloc((length + 1)*sizeof(char));
	memset(result, 0, sizeof(char) * (length + 1));
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, result, length, NULL, NULL);
	return result;
}

// use free()
char *ansi_to_utf_8(const char *str) {
    wchar_t *wstr = ansi_to_utf_16(str);
    char *result = utf_16_to_utf_8(wstr);
    free(wstr);
    return result;
}

// use free()
char *utf_8_to_ansi(const char *wstr) {
	wchar_t *str = utf_8_to_utf_16(wstr);
    char *result = utf_16_to_ansi(str);
    free(str);
    return result;
}

}
}
