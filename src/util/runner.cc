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

typedef void (*callback_t)(void *, void *, void *, void*);

struct CallParam {
  callback_t callback;
  SyncData *sync_data;
  bool wait;
  void *p0;
  void *p1;
  void *p2;
  void *p3;
};

void glib_destroy_notify(gpointer data)
{
  SyncData *sync_data = reinterpret_cast<SyncData *>(data);
  g_mutex_clear(&sync_data->mutex);
  g_cond_clear(&sync_data->cond);
  delete sync_data;
}

gboolean gtk_source_func(CallParam &data)
{
  data.callback(data.p0, data.p1, data.p2, data.p3);
  if (data.wait) g_cond_signal(&data.sync_data->cond);

  delete &data;
  return false;
}

void call(void *callback, bool wait,
          void *p0, void *p1, void *p2, void *p3)
{
  SyncData *sync_data = reinterpret_cast<SyncData *>(g_private_get(&key));
  if (sync_data == NULL) {
    sync_data = new SyncData;
    g_mutex_init(&sync_data->mutex);
    g_cond_init(&sync_data->cond);
    g_private_set(&key, sync_data);
  }

  CallParam &param = *(new CallParam);
  param.callback = reinterpret_cast<callback_t>(callback);
  param.sync_data = sync_data;
  param.wait = wait;
  param.p0 = p0;
  param.p1 = p1;
  param.p2 = p2;
  param.p3 = p3;

  gdk_threads_add_idle(reinterpret_cast<GSourceFunc>(gtk_source_func), &param);

  if (wait) {
    g_mutex_lock(&sync_data->mutex);
    g_cond_wait(&sync_data->cond, &sync_data->mutex);
    g_mutex_unlock(&sync_data->mutex);
  }
}

}  // namespace runner
}  // namespace util
}  // namespace yage
