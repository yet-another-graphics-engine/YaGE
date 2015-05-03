#include <gtk/gtk.h>
#include <algorithm>
#include "runner.h"

namespace yage {
namespace util {

Runner::Runner() {
  g_cond_init(&cond_);
  g_mutex_init(&mutex_);
}

Runner::~Runner() {
  g_cond_clear(&cond_);
  g_mutex_clear(&mutex_);
}

void Runner::call(callback_type fn, std::initializer_list<gpointer> param)
{
  gpointer *array_param = new gpointer[param.size()];
  std::copy(param.begin(), param.end(), array_param);

  g_mutex_lock(&mutex_);
  gdk_threads_add_idle(reinterpret_cast<GSourceFunc>(fn), array_param);
  g_cond_wait(&cond_, &mutex_);
  g_mutex_unlock(&mutex_);

  delete[] array_param;
}

void Runner::signal() {
  g_cond_signal(&cond_);
}

}  // namespace util
}  // namespace yage
