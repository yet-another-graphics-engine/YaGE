#include "test.h"
#include <vector>
#include <ctime>
void test_init(void);
using test_callback_t = void (*)(void);

vector<pair<test_callback_t, string>> g_tests;

void sleep_sec(int seconds) {
#ifdef _WIN32
  Sleep(1000 * seconds);
#else
  sleep(seconds);
#endif
}

extern "C" int yage_main()
{
  test_init();
  decltype(g_tests)::iterator test_iter = g_tests.end();

  if (yage::argc == 1) {
    // run the last test_iter
    --test_iter;
  } else if (yage::argc == 2) {
    // run the specified test_iter
    char *test_name = yage::argv[1];
    for (decltype(test_iter) i = g_tests.begin(); i != g_tests.end(); ++i) {
      if (i->second == test_name) {
        test_iter = i;
        break;
      }
    }
  }

  if (test_iter == g_tests.end()) {
    // not found
    fprintf(stderr, "ERROR: Failed to get the test.\n"
                    "Usage: %s test_name\n\n", yage::argv[0]);
    fprintf(stderr, "Availiable tests:\n");
    for (decltype(test_iter) i = g_tests.begin(); i != g_tests.end(); ++i) {
      fprintf(stderr, "\t%s\n", i->second.c_str());
    }
    return -1;
  }

  fprintf(stderr, "INFO: Running test_%s\n", test_iter->second.c_str());
  clock_t start_time = clock();

  test_iter->first();

  fprintf(stderr, "INFO: Test end, CPU time = %.2lfs\n",
                  static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC);
  return 0;
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

void test_init(void)
{
#define TEST_ADD(x) \
  void test_##x(void); \
  g_tests.push_back(pair<test_callback_t, string>(test_##x, #x))

  TEST_ADD(audio);
  TEST_ADD(dialog);
  TEST_ADD(fix_size);
  TEST_ADD(msg);
  TEST_ADD(resize);
  TEST_ADD(window_count);
  TEST_ADD(draw);
  TEST_ADD(draw_perf);
}

