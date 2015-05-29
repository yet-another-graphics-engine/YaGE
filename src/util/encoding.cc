#include "encoding.h"
#ifdef _WIN32
#include <windows.h>
#endif

namespace yage {
namespace util {

bool is_string_utf_8(const char *str,int str_length)
{
  int i;
  int nBytes = 0;
  unsigned char c;
  for(i = 0; i < str_length; i++)
  {
    c = *(str + i);
    if(nBytes == 0)
    {
      if((c & 0x80) == 0)               //ASCII 0XXX XXXX
        continue;
      if(c > 0xFD)
        return false;
      if(c >= 0xFC && c <= 0xFD)        //1111 110X
        nBytes = 6;
      else if(c >= 0xF8)                //1111 10XX
        nBytes = 5;
      else if(c >= 0xF0)                //1111 0XXX
        nBytes = 4;
      else if(c >= 0xE0)                //1110 XXXX
        nBytes = 3;
      else if(c >= 0xC0)                //110X XXXX
        nBytes = 2;
      else
        return false;
      nBytes--;
    }
    else
    {
      if((c & 0xC0) != 0x80)            //10XX XXXX & 1100 0000 (0xC0)
        return false;
      nBytes--;
    }
  }
  return true;
}

std::string convert_string(const std::string& str)
{
  if(is_string_utf_8(str.c_str(),str.length()))
    return str;
  else
  {
    char* utf8_str = ansi_to_utf_8(str.c_str());
    std::string result = utf8_str;
    free_string(utf8_str);
    return result;
  }
}

#ifdef _WIN32
wchar_t *ansi_to_utf_16(const char* str) {
	int length;
	wchar_t *result;
	length = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	result = new wchar_t[length + 1];
	memset(result, 0, (length + 1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, str, -1, result, length);
	return result;
}

char *utf_16_to_ansi(const wchar_t *wstr) {
	char *result;
	int length;
	length = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	result = new char[length + 1];
	memset(result, 0, sizeof(char) * (length + 1));
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, result, length, NULL, NULL);
	return result;
}

wchar_t *utf_8_to_utf_16(const char* str) {
	int length;
	wchar_t *result;
	length = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	result = new wchar_t[length + 1];
	memset(result, 0, (length + 1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, result, length);
	return result;
}

char *utf_16_to_utf_8(const wchar_t *wstr) {
	char *result;
	int length;
	length = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	result = new char[length + 1];
	memset(result, 0, sizeof(char) * (length + 1));
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, result, length, NULL, NULL);
	return result;
}
#endif

char *ansi_to_utf_8(const char *str) {
#ifdef _WIN32
	wchar_t *wstr = ansi_to_utf_16(str);
	char *result = utf_16_to_utf_8(wstr);
	delete wstr;
	return result;
#else
	return const_cast<char *>(str);
#endif
}

char *utf_8_to_ansi(const char *wstr) {
#ifdef _WIN32
	wchar_t *str = utf_8_to_utf_16(wstr);
    char *result = utf_16_to_ansi(str);
    delete str;
    return result;
#else
	return const_cast<char *>(wstr);
#endif
}

void free_string(char *str) {
#ifdef _WIN32
	delete str;
#else
#endif
}

}
}
