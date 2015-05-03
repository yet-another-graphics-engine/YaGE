#ifndef SYNC_CC_TBADOQUZ
#define SYNC_CC_TBADOQUZ
#include <glib.h>
#include <initializer_list>

namespace yage {
namespace util {

class Runner {
private:
  GCond cond_;
  GMutex mutex_;

public:
  using callback_type = gboolean (*)(gpointer *param);

  Runner();
  ~Runner();
  void call(callback_type fn, std::initializer_list<gpointer> param);
  void signal();
};

}  // namespace util
}  // namespace yage
#endif /* end of include guard: SYNC_CC_TBADOQUZ */
