#ifndef YAGE_INC_COMMON_H_
#define YAGE_INC_COMMON_H_

/**
 * \~english @brief main function redirect
 * DO NOT INCLUDE THIS HEADER TO WRITE PROGRAM THAT DO NOT LINK TO YAGE
 *
 * \~chinese @brief main 函数重定向
 * 请勿在不链接到 YaGE 的程序中包含此头文件
*/
#ifdef __cplusplus
#define main(...) \
  * _yage_dummy_var = NULL; \
  int yage_main(int argc, char *argv[]); \
  extern "C" int yage_lib_init(int argc, char **argv, int (*yage_main)(int, char**)); \
  int main(int argc, char *argv[]) { \
    return yage_lib_init(argc, argv, yage_main); \
  } \
  int yage_main(int argc, char *argv[])
#else
#define main(...) \
  _yage_dummy_func() {} \
  int yage_main(int argc, char *argv[]); \
  int yage_lib_init(int argc, char **argv, int (*yage_main)(int, char**)); \
  int main(int argc, char *argv[]) { \
    return yage_lib_init(argc, argv, yage_main); \
  } \
  int yage_main(int argc, char *argv[])
#endif

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
#else
#if _MSC_VER < 1600
#include "stdint.h"
#else
#include <stdint.h>
#endif
#endif

#include "msvc.h"

#endif  // YAGE_INC_COMMON_H_
