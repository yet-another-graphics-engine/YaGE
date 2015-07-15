#ifndef YAGE_INC_COMMON_H_
#define YAGE_INC_COMMON_H_

/**
 * \~english @brief main function redirect
 * DO NOT INCLUDE THIS HEADER TO WRITE PROGRAM THAT DO NOT LINK TO YAGE
 *
 * \~chinese @brief main 函数重定向
 * 请勿在不链接到 YaGE 的程序中包含此头文件
*/
#if defined(YAGE_CONSOLE) || !defined(_MSC_VER)
#ifdef __cplusplus
#define main(...) \
  * _yage_dummy_var = 0; \
  int yage_main(int argc, char *argv[]); \
  extern "C" int yage_lib_init(int argc, char **argv, int (*yage_main)(int, char**)); \
  int main(int argc, char *argv[]) { \
    return yage_lib_init(argc, argv, yage_main); \
  } \
  int yage_main(int argc, char *argv[])
#else // __cplusplus
#define main(...) \
  _yage_dummy_func() {} \
  int yage_main(int argc, char *argv[]); \
  int yage_lib_init(int argc, char **argv, int (*yage_main)(int, char**)); \
  int main(int argc, char *argv[]) { \
    return yage_lib_init(argc, argv, yage_main); \
  } \
  int yage_main(int argc, char *argv[])
#endif // __cplusplus
#else // defined(YAGE_CONSOLE) || !defined(_MSC_VER)
#include <stdlib.h> // for __argc and __argv
#ifdef __cplusplus
#define main(...) \
   * _yage_dummy_var = 0; \
  int yage_main(int argc, char *argv[]); \
  extern "C" int yage_lib_init(int argc, char **argv, int (*yage_main)(int, char**)); \
  __pragma(comment(linker, "/subsystem:windows")) \
  struct HINSTANCE__; \
  typedef HINSTANCE__ *HINSTANCE; \
  int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char *lpCmdLine, int nCmdShow) { \
    int argc = __argc; \
    char **argv = __argv; \
    return yage_lib_init(argc, argv, yage_main); \
  } \
  int yage_main(int argc, char *argv[])
#else // __cplusplus
#define main(...) \
  yage_dummy_func() {} \
  int yage_main(int argc, char *argv[]); \
  int yage_lib_init(int argc, char **argv, int (*yage_main)(int, char**)); \
  __pragma(comment(linker, "/subsystem:windows")) \
  int __stdcall WinMain(void *hInstance, void *hPrevInstance, char *lpCmdLine, int nCmdShow) { \
    int argc = __argc; \
    char **argv = __argv; \
    return yage_lib_init(argc, argv, yage_main); \
  } \
  int yage_main(int argc, char *argv[])
#endif // __cplusplus
#endif // defined(YAGE_CONSOLE) || !defined(_MSC_VER)

/*
 * `main` macro description
 *  Users from different world of C/C++ may write many variations of `main` function.
 *  Such as:
 *  in C  : main(); void main(); int main(); and ones with void argument or argc plus argv
 *  in C++: similarly like C, but bare main() is not allowed because every function must return something.
 *  So we did this macro:
 *  Under C++ mode, void/int main extracts an pointer variable and two core functions by us.
 *  Under C mode, void/int/(none) main extracts an empty function (just like main, C allows function with a return type returns nothing), and two core functions by us.
 */


#ifndef _MSC_VER

#include <stdint.h>

#else  // ifndef _MSC_VER

#if _MSC_VER < 1600
#include "stdint.h"
#else  // if _MSC_VER < 1600
#include <stdint.h>
#endif  // if _MSC_VER < 1600

#ifndef NAN
// NAN solution from http://tdistler.com/
static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
#define NAN (*(const float *) __nan)
#endif  // ifndef NAN

#endif  // ifndef _MSC_VER

#include "msvc.h"

#endif  // YAGE_INC_COMMON_H_
