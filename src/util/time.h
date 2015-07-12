#include <gtk/gtk.h>
#ifndef _MSC_VER
#include <stdint.h>
#else
#if _MSC_VER < 1600
#include "../../include/yage/stdint.h"
#else
#include <stdint.h>
#endif
#endif

namespace yage {
namespace util {
namespace time {

inline uint32_t get_timestamp() {
  return static_cast<int>(g_get_monotonic_time() / 1000);
}

}  // namespace runner
}  // namespace util
}  // namespace yage
