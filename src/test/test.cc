#include "test.h"
#include "../main.h"
#include <vector>
#include <ctime>
typedef void (*test_callback_t)(void);
typedef vector<pair<test_callback_t, string> > test_container_t;
test_container_t g_tests;
typedef test_container_t::iterator test_iter_t;

void test_init(void);

void sleep_sec(int seconds) {
#ifdef _WIN32
  Sleep(1000 * seconds);
#else
  sleep(seconds);
#endif
}

bool fuzzy_string_match(const string &lazy, const string &full) {
  string::const_iterator j = full.begin();

  for (string::const_iterator i = lazy.begin(); i != lazy.end(); ++i) {
    for (; j != full.end(); ++j) {
      if (*i == *j) goto match_next;
    }
    return false;

match_next:
    continue;
  }
  return true;
}

void test_show_list() {
  fprintf(stderr, "Availiable tests:\n");
  for (test_iter_t i = g_tests.begin(); i != g_tests.end(); ++i) {
    fprintf(stderr, "\t%s\n", i->second.c_str());
  }
}

void test_show_usage() {
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "\t%s test_name\n", yage::argv[0]);
  fprintf(stderr, "\t%s !\n", yage::argv[0]);
}

test_iter_t test_match(const string &lazy_name) {
  test_iter_t test_iter = g_tests.end();
  double match_percent = 0;

  for (test_iter_t i = g_tests.begin(); i != g_tests.end(); ++i) {
    if (!fuzzy_string_match(lazy_name, i->second)) continue;
    double current_match_percent = static_cast<double>(lazy_name.size()) /
                                   i->second.size();
    if (current_match_percent > match_percent) {
      test_iter = i;
      match_percent = current_match_percent;
    }
  }
  return test_iter;
}

void test_run(test_iter_t test_iter) {
  fprintf(stderr, "INFO: Running test_%s()\n", test_iter->second.c_str());
  clock_t start_time = clock();

  test_iter->first();

  fprintf(stderr, "INFO: Test end, CPU time = %.2lfs\n",
                  static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC);
}

extern "C" int yage_main(int argc, char **argv) {
  test_init();

  if (argc == 1) {
    test_run(--g_tests.end());
    return 0;
  }

  if (argc == 2) {
    string test_name = argv[1];
    if (test_name == "!") {
      test_show_list();
      return 0;
    }

    test_iter_t test_iter = test_match(test_name);
    if (test_iter != g_tests.end()) {
      test_run(test_iter);
      return 0;
    } else {
      fprintf(stderr, "ERROR: Failed to match the test.\n");
      return -1;
    }
  }

  test_show_usage();
  return -2;
}

int main(int argc, char **argv) {
    return yage_lib_init(argc, argv, yage_main);
}
/*
 * To add tests to framework:
 *
 * 0. Write void test_xxx() in src/test/xxx.cc
 * 1. Edit src/CMakeListst.txt, add "src/xxx.cc"
 * 2. Add "TEST_ADD(xxx)" at the end of "void test_init(void)"
 * 3. Your code will be run by default
 * 4. Execute "bin/yagetest xxx" to run a specific test
 */

void test_init(void) {
#define TEST_ADD(x) \
  void test_##x(void); \
  g_tests.push_back(pair<test_callback_t, string>(test_##x, #x))

  TEST_ADD(audio);
  TEST_ADD(dialog);
  TEST_ADD(draw_shape);
  TEST_ADD(draw_anim);
  TEST_ADD(window_count);
  TEST_ADD(window_fix_size);
  TEST_ADD(window_msg);
  TEST_ADD(window_resize);
  TEST_ADD(draw_pic);
  TEST_ADD(draw_perf);
  TEST_ADD(api_yage);
  TEST_ADD(api_bgi);
  TEST_ADD(api_yage_perf);
  TEST_ADD(timer);
}

