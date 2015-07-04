#include "font.h"
#include "../util/encoding.h"
#ifdef _WIN32
#include <glib.h>
#define PANGO_ENABLE_ENGINE
#include <pango/pangowin32.h>
#include <windef.h>
#include <wingdi.h>
static LOGFONT* win32_default_font = NULL;
#endif // _WIN32

namespace yage {
namespace draw {

#ifdef __WIN32
//const char* Font::yage_default_font_ = get_win32_default_font_family();
const char* Font::yage_default_font_ = "Tahoma";
#elif defined(__APPLE__)
#if MAC_OS_X_VERSION_MIN_REQUIRED <= MAC_OS_X_VERSION_10_9
const char* Font::yage_default_font_ = "Lucida Grande";
#else
const char* Font::yage_default_font_ = "Helvetica Neue";
#endif
#else
const char* Font::yage_default_font_ = "Sans Serif";
#endif

Font::Font(const std::string &family, int size, bool is_bold, bool is_italic) {
  description_ = pango_font_description_new();
  set_font_family(family);
  set_size(size);
  set_bold_status(is_bold);
  set_italic_status(is_italic);
}

Font::Font(Font& font) {
  description_ = pango_font_description_copy(font.pro_get_pango_font());
}

Font &Font::operator=(Font &font) {
  if (this != &font) {
    pango_font_description_free(description_);
    description_ = pango_font_description_copy(font.pro_get_pango_font());
  }
  return *this;
}

Font::~Font() {
  pango_font_description_free(description_);
}

#ifdef _WIN32
#define MAKE_TT_TABLE_NAME(c1, c2, c3, c4) \
   (((guint32)c4) << 24 | ((guint32)c3) << 16 | ((guint32)c2) << 8 | ((guint32)c1))
#define NAME_TABLE (MAKE_TT_TABLE_NAME('n','a','m','e'))

const char* Font::get_win32_default_font_family()
{
  if(win32_default_font == NULL)
  {
    win32_default_font = g_new(LOGFONT, 1);
    SystemParametersInfo(SPI_GETICONTITLELOGFONT, sizeof(LOGFONT), win32_default_font, 0);
    yage_default_font_ = win32_default_font->lfFaceName;
  }
  return yage_default_font_;
}

struct name_header {
  guint16 format_selector;
  guint16 num_name_records;
  guint16 string_storage_offset;
};

struct name_record {
  guint16 platform_ID;
  guint16 encoding_ID;
  guint16 language_ID;
  guint16 name_ID;
  guint16 string_length;
  guint16 string_offset;
};

bool get_name_header(HDC hdc, name_header& header) {
  if (GetFontData (hdc, NAME_TABLE, 0, &header, sizeof(header)) != sizeof (header))
    return false;
  header.num_name_records = GUINT16_FROM_BE (header.num_name_records);
  header.string_storage_offset = GUINT16_FROM_BE (header.string_storage_offset);
  return true;
}

bool get_name_record(HDC hdc, int nth_record, name_record& record) {
  if(GetFontData (hdc, NAME_TABLE, 6 + nth_record * sizeof (record),
		   &record, sizeof (record)) != sizeof (record))
    return false;

  record.platform_ID = GUINT16_FROM_BE (record.platform_ID);
  record.encoding_ID = GUINT16_FROM_BE (record.encoding_ID);
  record.language_ID = GUINT16_FROM_BE (record.language_ID);
  record.name_ID = GUINT16_FROM_BE (record.name_ID);
  record.string_length = GUINT16_FROM_BE (record.string_length);
  record.string_offset = GUINT16_FROM_BE (record.string_offset);
  return true;
}

bool get_name_record_string(HDC hdc, int offset, size_t str_length, char* str) {
  if(GetFontData(hdc, NAME_TABLE, offset, str, str_length) != str_length)
    return false;
  return true;
}

std::string Font::get_win32_font_family_eng_name(const std::string& font_family) {
  if(yage::util::is_string_ASCII(font_family.c_str(), font_family.length()))
    return font_family;

  if(win32_default_font == NULL)
    get_win32_default_font_family();

  bool ansi_flag = false;
  const char* ansi_font_family;
  if(yage::util::is_string_utf_8(font_family.c_str(), font_family.length()))
  {
    ansi_flag = true;
    ansi_font_family = yage::util::utf_8_to_ansi(font_family.c_str());
  }
  else
    ansi_font_family = font_family.c_str();

  HDC hdc = pango_win32_get_dc();
  LOGFONT lgf = *win32_default_font;
  HFONT hfont, oldhfont;
#if defined(_MSC_VER) && _MSC_VER > 1300
  strcpy_s(lgf.lfFaceName, 32, ansi_font_family);
#else
  strcpy(lgf.lfFaceName, ansi_font_family);
#endif
  std::string temp_result;
  char* result, *name;
  const char* charset;
  int i, target = -1;
  name_header header;
  name_record record;

  if(ansi_flag)
    yage::util::free_string(const_cast<char*>(ansi_font_family));

  hfont = CreateFontIndirect(&lgf);
  if(hfont == NULL)
    goto fail;
  oldhfont = (HFONT)SelectObject(hdc, hfont);
  if(oldhfont == NULL)
  {
    DeleteObject(hfont);
    goto fail;
  }

  if(get_name_header(hdc, header) == false)
    goto fail2;
  for(i = 0; i < header.num_name_records; i++)
  {
    if(get_name_record(hdc, i, record) == false)
      goto fail2;
    if(record.name_ID != 1 || record.string_length <= 0)
      continue;

    if(record.platform_ID == 3 && PRIMARYLANGID(record.language_ID) == LANG_ENGLISH)  //Microsoft Platform
    {
      target = i;
      charset = "UTF-16BE";
    }
    else if(record.platform_ID == 1 && target < 0)                                  //Macintosh Platform
    {
      if(record.encoding_ID == 0 && record.language_ID == 0)                        //Roman encoding and English language
      {
        target = i;
        charset = "MacRoman";
      }
    }
    else if((record.platform_ID == 0 || record.platform_ID == 2) && target < 0)     //Apple Unicode or ISO platform
    {
      target = i;
      charset = "UCS-4BE";
    }
  }
  if(target < 0)
    goto fail2;
  get_name_record(hdc, target, record);
  result = g_new(char, record.string_length + 1);
  if(get_name_record_string(hdc, header.string_storage_offset + record.string_offset, record.string_length, result) == false)
  {
    g_free(result);
    goto fail2;
  }
  result[record.string_length] = '\0';
  name = g_convert(result, record.string_length, "UTF-8", charset, NULL, NULL, NULL);
  temp_result = name;
  g_free(result);
  g_free(name);
  SelectObject(hdc, oldhfont);
  DeleteObject(hfont);

  return temp_result;

  fail2:
  SelectObject(hdc, oldhfont);
  DeleteObject(hfont);
  fail:
  return yage::util::convert_string(font_family);
}

#endif // _WIN32

std::string Font::get_font_family_yage_default() {
  #ifdef _WIN32
  return yage::util::convert_string(get_win32_default_font_family());
  #else
  return yage_default_font_;
  #endif // _WIN32
}

std::string Font::get_font_family(void) const {
  return pango_font_description_get_family(description_);
}

int Font::get_size(void) const {
  return pango_font_description_get_size(description_) / PANGO_SCALE;
}

bool Font::get_bold_status(void) const {
  return pango_font_description_get_weight(description_) > PANGO_WEIGHT_NORMAL;
}

bool Font::get_italic_status(void) const {
  return pango_font_description_get_style(description_) != PANGO_STYLE_NORMAL;
}

void Font::set_font_family(const std::string &family) {
  #ifdef _WIN32
  std::string utf_8_family = get_win32_font_family_eng_name(family);
  #else
  std::string utf_8_family = yage::util::convert_string(family.c_str());
  #endif // _WIN32
  pango_font_description_set_family(description_, utf_8_family.c_str());
}

void Font::set_size(int size) {
  pango_font_description_set_size(description_, size * PANGO_SCALE);
}

void Font::set_bold_status(bool is_bold) {
  if (is_bold) {
      pango_font_description_set_weight(description_, PANGO_WEIGHT_BOLD);
  } else {
      pango_font_description_set_weight(description_, PANGO_WEIGHT_NORMAL);
  }
}

void Font::set_italic_status(bool is_italic) {
  if (is_italic) {
      pango_font_description_set_style(description_, PANGO_STYLE_ITALIC);
  } else {
      pango_font_description_set_style(description_, PANGO_STYLE_NORMAL);
  }
}

PangoFontDescription *Font::pro_get_pango_font(void) const {
  return description_;
}

void Font::pro_set_pango_font(PangoFontDescription *description) {
  if (description_) this->~Font();
  description_ = description;
}

}
}
