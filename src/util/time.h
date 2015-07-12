#include <gtk/gtk.h>
#include <stdint.h>

namespace yage {
namespace util {
namespace time {

inline uint32_t get_timestamp() {
  return g_get_monotonic_time() / 1000;
}

}  // namespace runner
}  // namespace util
}  // namespace yage
