#include "main.h"
#include "window/window.h"

namespace yage {

int argc;
char **argv;

}  // namespace yage

namespace {
using namespace yage;

gpointer user_thread(gpointer *param) {
  yage_main_t func = reinterpret_cast<yage_main_t>(param[0]);
  int &ret = *reinterpret_cast<int *>(param[1]);

  ret = func(argc, argv);
  gtk_main_quit();
  return NULL;
}

}  // namespace

extern "C" int yage_lib_init(int argc, char **argv, yage_main_t yage_main) {
  yage::argc = argc;
  yage::argv = argv;

  yage::window::init();

  int ret = 0;
  gpointer param[] = {reinterpret_cast<gpointer>(yage_main), &ret};
  g_thread_new("YaGE user", reinterpret_cast<GThreadFunc>(user_thread), param);
  gtk_main();

  // user_thread() will set the value of ret
  return ret;
}
