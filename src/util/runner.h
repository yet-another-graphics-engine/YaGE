#ifndef UTIL_RUNNER_H_
#define UTIL_RUNNER_H_
#include <glib.h>

namespace yage {
namespace util {
namespace runner {

void call(void *callback, bool wait,
          void *p0 = nullptr,
          void *p1 = nullptr,
          void *p2 = nullptr,
          void *p3 = nullptr);

}  // namespace runner
}  // namespace util
}  // namespace yage

#define runner_call_ex(fn, wait, ...) \
  yage::util::runner::call(reinterpret_cast<void *>(fn), (wait), __VA_ARGS__)

#define runner_call(fn, ...) runner_call_ex(fn, true, __VA_ARGS__)

#endif
