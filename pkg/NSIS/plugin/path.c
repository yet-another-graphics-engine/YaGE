/** NSIS Plugin to modify PATH environment variable
 *
 * Copyright (c) 2015 Xiaodong Qi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <windows.h>
#include "pluginapi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Find directory inside a Windows-style PATH variable
 *
 * @param dir directory to find
 * @param path PATH variable
 * @param size the pointer to size to store size of directory name, can be set to NULL
 * @param rawsize the pointer to size of raw version of dir
 * @return The position the first to be removed
 */
static inline TCHAR *FindPathInsidePath(const TCHAR *dir, const TCHAR *path, int *size) {
  TCHAR *dir_copy = (TCHAR *)malloc((_tcslen(dir) + 1) * sizeof(TCHAR));
  memset(dir_copy, 0, (_tcslen(dir) + 1) * sizeof(TCHAR));
  _tcsnccpy(dir_copy, dir, _tcslen(dir));
  for (TCHAR *dir_iterator = dir_copy + _tcslen(dir) - 1; dir_iterator > dir_copy; dir_iterator--) {
    if (*dir_iterator == _T('\\')) {
      dir_iterator[0] = _T('\0');
    } else {
      break;
    }
  }
  int raw_size = _tcslen(dir_copy);
  TCHAR *remain_string = (TCHAR *)path;
  TCHAR *return_string = NULL;
  int return_size = _tcslen(dir_copy);
  while (remain_string < path + _tcslen(path)) {
    remain_string = _tcsstr(remain_string, dir_copy);
    if (!remain_string) { // No search found
      break;
    }
    if (remain_string >= path) {
      if (*(remain_string - 1) == _T(';')) { // prefix ';'
        return_string = remain_string - 1;
        return_size++;
      } else {
        return_string = remain_string;
      }
      if (*(remain_string + _tcslen(dir_copy)) == _T('\\')) { // postfix '\\'
        return_size++;
        if (*(remain_string + _tcslen(dir_copy) + 1) == _T(';')) { // postfix '\\;'
          return_size++;
          break;
        } else {
          if (return_string + return_size >= path + _tcslen(path)) {
            break;
          } else {
            return_string = NULL;
            return_size = _tcslen(dir_copy);
            remain_string += _tcslen(dir_copy);
            continue;
          }
        }
      } else if (*(remain_string + _tcslen(dir_copy)) == _T(';')) { // postfix ';'
        return_size++;
        break;
      } else {
        if (return_string + return_size >= path + _tcslen(path)) {
          break;
        } else {
          return_string = NULL;
          return_size = _tcslen(dir_copy);
          remain_string += _tcslen(dir_copy);
          continue;
        }
      }
    }
  }
  free(dir_copy);
  if (size) {
    *size = return_size;
  }
  return return_string;
}

static inline wchar_t *ansi_to_utf_16(const char* str) {
	int length = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
	wchar_t *result = (wchar_t *)malloc((length + 1)*sizeof(wchar_t));
	memset(result, 0, (length + 1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, 0, str, -1, result, length);
	return result;
}

static inline char *utf_16_to_ansi(const wchar_t *wstr) {
	int length = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char *result = (char *)malloc((length + 1)*sizeof(char));
	memset(result, 0, sizeof(char) * (length + 1));
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, result, length, NULL, NULL);
	return result;
}

static inline wchar_t *utf_8_to_utf_16(const char* str) {
	int length = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	wchar_t *result = (wchar_t *)malloc((length + 1)*sizeof(wchar_t));
	memset(result, 0, (length + 1)*sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, result, length);
	return result;
}

static inline char *utf_16_to_utf_8(const wchar_t *wstr) {
	int length = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char *result = (char *)malloc((length + 1)*sizeof(char));
	memset(result, 0, sizeof(char) * (length + 1));
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, result, length, NULL, NULL);
	return result;
}

static inline char *ansi_to_utf_8(const char *str) {
	wchar_t *wstr = ansi_to_utf_16(str);
	char *result = utf_16_to_utf_8(wstr);
	free(wstr);
	return result;
}

static inline char *utf_8_to_ansi(const char *wstr) {
	wchar_t *str = utf_8_to_utf_16(wstr);
  char *result = utf_16_to_ansi(str);
  free(str);
  return result;
}

static inline void __AddToPath(const TCHAR *path) {
  HKEY env_hkey;
  LONG reg_open_return = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("System\\CurrentControlSet\\Control\\Session Manager\\Environment"), 0, KEY_ALL_ACCESS, &env_hkey);
  if (reg_open_return == ERROR_SUCCESS) {
    DWORD path_original_length;
    RegQueryValueEx(env_hkey, _T("Path"), NULL, NULL, NULL, &path_original_length);
    TCHAR *path_original = (TCHAR *)malloc(path_original_length + sizeof(TCHAR));
    LONG c = RegQueryValueEx(env_hkey, _T("Path"), NULL, NULL, (LPBYTE)path_original, &path_original_length);
    path_original_length /= sizeof(TCHAR);
    TCHAR *path_pos;
    if (path_pos = FindPathInsidePath(path, path_original, NULL)) {
      _ftprintf(stderr, _T("Path already added"));
    } else {
      _ftprintf(stderr, _T("%s\n with length %ld"), path_original, path_original_length);
      TCHAR *path_new = (TCHAR *)malloc((path_original_length + _tcslen(path) + 1) * sizeof(TCHAR));
      _tcsnccpy(path_new, path_original, path_original_length);
      _tcscpy(path_new + path_original_length - 1, _T(";"));
      _tcscpy(path_new + path_original_length, path);
      RegSetValueEx(env_hkey, _T("Path"), 0, REG_EXPAND_SZ, (LPBYTE)path_new, (path_original_length + _tcslen(path) + 1) * sizeof(TCHAR));
    }
    RegCloseKey(env_hkey);
    SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment", SMTO_ABORTIFHUNG, 3000, NULL);
    SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)L"Environment", SMTO_ABORTIFHUNG, 3000, NULL);
  } else {
    _ftprintf(stderr, _T("Key opened error."));
  }
}

void __declspec(dllexport) AddToPath(HWND hwndParent, int string_size, TCHAR *variables, stack_t **stacktop, extra_parameters *extra) {
  EXDLL_INIT();
  TCHAR path[1024];
  popstringn(path, 1024);
  __AddToPath(path);
}

static inline void __RemoveFromPath(const TCHAR *path) {
  HKEY env_hkey;
  LONG reg_open_return = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("System\\CurrentControlSet\\Control\\Session Manager\\Environment"), 0, KEY_ALL_ACCESS, &env_hkey);
  if (reg_open_return == ERROR_SUCCESS) {
    DWORD path_original_length;
    RegQueryValueEx(env_hkey, _T("Path"), NULL, NULL, NULL, &path_original_length);
    TCHAR *path_original = (TCHAR *)malloc(path_original_length + sizeof(TCHAR));
    RegQueryValueEx(env_hkey, _T("Path"), NULL, NULL, (LPBYTE)path_original, &path_original_length);
    path_original_length /= sizeof(TCHAR);
    int path_length = 0;
    TCHAR *path_pos;
    if (path_pos = FindPathInsidePath(path, path_original, &path_length)) {
      TCHAR *path_new = (TCHAR *)malloc((path_original_length - path_length + 1) * sizeof(TCHAR));
      _tcsnccpy(path_new, path_original, path_pos - path_original);
      _tcsnccpy(path_new + (path_pos - path_original), _T(";"), 1);
      _tcsnccpy(path_new + (path_pos - path_original) + 1, path_pos + path_length, path_original + path_original_length - path_pos - path_length);
      TCHAR *path_final = path_new;
      while (path_final < path_new + _tcslen(path_new)) {
        if (*path_final == _T(';')) {
          path_final++;
        } else {
          break;
        }
      }
      int path_final_size = _tcslen(path_final);
      while (path_final_size > 0) {
        if (*(path_final + path_final_size - 1) == _T(';')) {
          path_final_size--;
        } else {
          break;
        }
      }
      path_final[path_final_size] = _T('\0');
      path_final_size++; // RegSetValueEx required NULL terminated size
      path_final_size *= sizeof(TCHAR);

      RegSetValueEx(env_hkey, _T("Path"), 0, REG_EXPAND_SZ, (LPBYTE)path_final, path_final_size);
    } else {
      _ftprintf(stderr, _T("Path already removed"));
    }
    RegCloseKey(env_hkey);
    SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment", SMTO_ABORTIFHUNG, 3000, NULL);
    SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)L"Environment", SMTO_ABORTIFHUNG, 3000, NULL);

  } else {
    _ftprintf(stderr, _T("Key opened error."));
  }
}

void __declspec(dllexport) RemoveFromPath(HWND hwndParent, int string_size, TCHAR *variables, stack_t **stacktop, extra_parameters *extra) {
  EXDLL_INIT();
  TCHAR path[1024];
  popstringn(path, 1024);
  __RemoveFromPath(path);
}

void __declspec(dllexport) AnsiToUtf8(HWND hwndParent, int string_size, TCHAR *variables, stack_t **stacktop, extra_parameters *extra) {
  EXDLL_INIT();
  TCHAR path[1024];
  popstringn(path, 1024);
  setuservariable(INST_8, ansi_to_utf_8(path));
}

void __declspec(dllexport) Utf8ToAnsi(HWND hwndParent, int string_size, TCHAR *variables, stack_t **stacktop, extra_parameters *extra) {
  EXDLL_INIT();
  TCHAR path[1024];
  popstringn(path, 1024);
  setuservariable(INST_9, utf_8_to_ansi(path));
}

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  return TRUE;
}

