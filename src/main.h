#ifndef YAGE_MAIN_H_
#define YAGE_MAIN_H_

namespace yage {

extern int argc;
extern char **argv;

extern const int version_major;
extern const int version_minor;
extern const int version_patch;
extern const char *version_string;

}  // namespace yage

typedef int (*yage_main_t)(int argc, char *argv[]);
extern "C" int yage_lib_init(int argc, char **argv, yage_main_t yage_main);

#endif /* end of include guard: YAGE_H_MDXUGEJV */
