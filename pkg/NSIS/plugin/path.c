/**
 * NSIS Plugin to modify PATH environment variable
 *
 * Copyright (c) 2015 Xiaodong Qi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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
static inline char *FindPathInsidePath(const char *dir, const char *path, int *size) {
    char *dir_copy = (char *)malloc(strlen(dir) + 1);
    memset(dir_copy, 0, strlen(dir) + 1);
    strncpy(dir_copy, dir, strlen(dir));
    for (char *dir_iterator = dir_copy + strlen(dir) - 1; dir_iterator > dir_copy; dir_iterator--) {
        if (*dir_iterator == '\\') {
            dir_iterator[0] = '\0';
        } else {
            break;
        }
    }
    int raw_size = strlen(dir_copy);
    char *remain_string = (char *)path;
    char *return_string = NULL;
    int return_size = strlen(dir_copy);
    while (remain_string < path + strlen(path)) {
        remain_string = strstr(remain_string, dir_copy);
        if (!remain_string) { // No search found
            break;
        }
        if (remain_string >= path) {
            if (*(remain_string - 1) == ';') { // prefix ';'
                return_string = remain_string - 1;
                return_size++;
            } else {
                return_string = remain_string;
            }
            if (*(remain_string + strlen(dir_copy)) == '\\') { // postfix '\\'
                return_size++;
                if (*(remain_string + strlen(dir_copy) + 1) == ';') { // postfix '\\;'
                    return_size++;
                    break;
                } else {
                    if (return_string + return_size >= path + strlen(path)) {
                        break;
                    } else {
                        return_string = NULL;
                        return_size = strlen(dir_copy);
                        remain_string += strlen(dir_copy);
                        continue;
                    }
                }
            } else if (*(remain_string + strlen(dir_copy)) == ';') { // postfix ';'
                return_size++;
                break;
            } else {
                if (return_string + return_size >= path + strlen(path)) {
                    break;
                } else {
                    return_string = NULL;
                    return_size = strlen(dir_copy);
                    remain_string += strlen(dir_copy);
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

static inline void __AddToPath(const char *path) {
    HKEY env_hkey;
    LONG reg_open_return = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "System\\CurrentControlSet\\Control\\Session Manager\\Environment", 0, KEY_ALL_ACCESS, &env_hkey);
    if (reg_open_return == ERROR_SUCCESS) {
        DWORD path_original_length;
        RegQueryValueExA(env_hkey, "Path", NULL, NULL, NULL, &path_original_length);
        char *path_original = (char *)malloc(path_original_length + 1);
        RegQueryValueExA(env_hkey, "Path", NULL, NULL, (LPBYTE)path_original, &path_original_length);
        char *path_pos;
        if (path_pos = FindPathInsidePath(path, path_original, NULL)) {
            fprintf(stderr, "Path already added");
        } else {
            fprintf(stderr, "%s\n with length %ld", path_original, path_original_length);
            char *path_new = (char *)malloc(path_original_length + strlen(path) + 1);
            strncpy(path_new, path_original, path_original_length);
            strcpy(path_new + path_original_length - 1, ";");
            strcpy(path_new + path_original_length, path);
            RegSetValueExA(env_hkey, "Path", 0, REG_EXPAND_SZ, (LPBYTE)path_new, path_original_length + strlen(path) + 1);
        }
        RegCloseKey(env_hkey);
      PostMessage(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment");
    } else {
        fprintf(stderr, "Key opened error.");
    }
}

void __declspec(dllexport) AddToPath(HWND hwndParent, int string_size, char *variables, stack_t **stacktop, extra_parameters *extra) {
  EXDLL_INIT();
  char path[1024];
  popstringn(path, 1024);
  __AddToPath(path);
}

static inline void __RemoveFromPath(const char *path) {
    HKEY env_hkey;
    LONG reg_open_return = RegOpenKeyExA(HKEY_LOCAL_MACHINE, "System\\CurrentControlSet\\Control\\Session Manager\\Environment", 0, KEY_ALL_ACCESS, &env_hkey);
    if (reg_open_return == ERROR_SUCCESS) {
        DWORD path_original_length;
        RegQueryValueExA(env_hkey, "Path", NULL, NULL, NULL, &path_original_length);
        char *path_original = (char *)malloc(path_original_length + 1);
        RegQueryValueExA(env_hkey, "Path", NULL, NULL, (LPBYTE)path_original, &path_original_length);
        int path_length = 0;
        char *path_pos;
        if (path_pos = FindPathInsidePath(path, path_original, &path_length)) {
            char *path_new = (char *)malloc(path_original_length - path_length + 1);
            strncpy(path_new, path_original, path_pos - path_original);
            memset(path_new + (path_pos - path_original), ';', 1);
            strncpy(path_new + (path_pos - path_original) + 1, path_pos + path_length, path_original + path_original_length - path_pos - path_length);
            char *path_final = path_new;
            while (path_final < path_new + strlen(path_new)) {
                if (*path_final == ';') {
                    path_final++;
                } else {
                    break;
                }
            }
            int path_final_size = strlen(path_final);
            while (path_final_size > 0) {
                if (*(path_final + path_final_size - 1) == ';') {
                    path_final_size--;
                } else {
                    break;
                }
            }
            path_final[path_final_size] = '\0';
            path_final_size++; // RegSetValueExA required NULL terminated size

            RegSetValueExA(env_hkey, "Path", 0, REG_EXPAND_SZ, (LPBYTE)path_final, path_final_size);
        } else {
            fprintf(stderr, "Path already removed");
        }
        RegCloseKey(env_hkey);
        PostMessage(HWND_BROADCAST, WM_SETTINGCHANGE, 0, (LPARAM)"Environment");
    } else {
        fprintf(stderr, "Key opened error.");
    }
}

void __declspec(dllexport) RemoveFromPath(HWND hwndParent, int string_size, char *variables, stack_t **stacktop, extra_parameters *extra) {
  EXDLL_INIT();
  char path[1024];
  popstringn(path, 1024);
  __RemoveFromPath(path);
}

BOOL WINAPI DllMain(HINSTANCE hInstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    return TRUE;
}

