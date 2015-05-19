#ifndef UTIL_RUNNER_H_
#define UTIL_RUNNER_H_
#include <glib.h>

namespace yage {
namespace util {
namespace runner {

void call(void *callback,
          void *p0 = nullptr,
          void *p1 = nullptr,
          void *p2 = nullptr,
          void *p3 = nullptr);

}  // namespace runner
}  // namespace util
}  // namespace yage

#define runner_call(fn, ...) \
  yage::util::runner::call(reinterpret_cast<void *>(fn), __VA_ARGS__)

#endif /* end of include guard: SYNC_CC_TBADOQUZ */
