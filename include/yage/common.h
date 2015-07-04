#ifndef YAGE_INC_COMMON_H_
#define YAGE_INC_COMMON_H_

/**
 * \~english @brief main function redirect
 * DO NOT INCLUDE THIS HEADER TO WRITE PROGRAM THAT DO NOT LINK TO YAGE
 *
 * \~chinese @brief main 函数重定向
 * 请勿在不链接到 YaGE 的程序中包含此头文件
 */
#define main(...) \
  _yage_dummy_func() {}\
  int yage_main(int argc, char *argv[]); \
  extern "C" int yage_lib_init(int argc, char **argv, int (*yage_main)(int, char**)); \
  int main(int argc, char *argv[]) { \
    return yage_lib_init(argc, argv, yage_main); \
  } \
  int yage_main(int argc, char *argv[])

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
