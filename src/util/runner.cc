#include <gtk/gtk.h>
#include <algorithm>
#include "runner.h"

namespace yage {
namespace util {
namespace runner {

void glib_destroy_notify(gpointer data);
GPrivate key = G_PRIVATE_INIT(glib_destroy_notify);

struct SyncData {
  GCond cond;
  GMutex mutex;
};

struct CallParam {
  void (*callback)(void *, void *, void *, void*);
  SyncData *sync_data;
  void *p0;
  void *p1;
  void *p2;
  void *p3;
};

void glib_destroy_notify(gpointer data)
{
  auto sync_data = reinterpret_cast<SyncData *>(data);
  g_mutex_clear(&sync_data->mutex);
  g_cond_clear(&sync_data->cond);
  delete sync_data;
}

gboolean gtk_source_func(CallParam &data)
{
  data.callback(data.p0, data.p1, data.p2, data.p3);
  g_cond_signal(&data.sync_data->cond);
  return false;
}

void call(void *callback, void *p0, void *p1, void *p2, void *p3)
{
  auto sync_data = reinterpret_cast<SyncData *>(g_private_get(&key));
  if (sync_data == nullptr) {
    sync_data = new SyncData;
    g_mutex_init(&sync_data->mutex);
    g_cond_init(&sync_data->cond);
    g_private_set(&key, sync_data);
  }

  CallParam param = {
    .callback = reinterpret_cast<decltype(CallParam::callback)>(callback),
    .sync_data = sync_data, .p0 = p0, .p1 = p1, .p2 = p2, .p3 = p3};

  g_mutex_lock(&sync_data->mutex);

  gdk_threads_add_idle(reinterpret_cast<GSourceFunc>(gtk_source_func), &param);

  g_cond_wait(&sync_data->cond, &sync_data->mutex);
  g_mutex_unlock(&sync_data->mutex);
}

}  // namespace runner
}  // namespace util
}  // namespace yage
