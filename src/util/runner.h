#ifndef UTIL_RUNNER_H_
#define UTIL_RUNNER_H_
#include <glib.h>

namespace yage {
namespace util {
namespace runner {

void call(void *callback, bool wait,
          void *p0 = NULL,
          void *p1 = NULL,
          void *p2 = NULL,
          void *p3 = NULL);

}  // namespace runner
}  // namespace util
}  // namespace yage

#if defined(_MSC_VER) && _MSC_VER < 1400
inline void runner_call_ex(void *callback, bool wait,
          void *p0 = NULL,
          void *p1 = NULL,
          void *p2 = NULL,
          void *p3 = NULL) {
  yage::util::runner::call(reinterpret_cast<void *>(callback), (wait), p0, p1, p2, p3);
}
inline void runner_call(void *callback,
          void *p0 = NULL,
          void *p1 = NULL,
          void *p2 = NULL,
          void *p3 = NULL) {
  yage::util::runner::call(reinterpret_cast<void *>(callback), true, p0, p1, p2, p3);
}
#else
#define runner_call_ex(fn, wait, ...) \
  yage::util::runner::call(reinterpret_cast<void *>(fn), (wait), __VA_ARGS__)

#define runner_call(fn, ...) runner_call_ex(fn, true, __VA_ARGS__)
#endif

#endif
