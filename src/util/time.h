#include <gtk/gtk.h>
#include "../../include/yage/stdint.h"

namespace yage {
namespace util {
namespace time {

inline uint32_t get_timestamp() {
  return static_cast<int>(g_get_monotonic_time() / 1000);
}

}  // namespace runner
}  // namespace util
}  // namespace yage
