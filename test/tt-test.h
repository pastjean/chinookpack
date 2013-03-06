#ifndef __TT_TEST_H
#define __TT_TEST_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M,...)              \
  do {                            \
    fprintf(stderr,               \
        "[DEBUG] (%s:%d)" M "\n", \
        __FILE__,                 \
        __LINE__,                 \
        ##__VA_ARGS__);           \
    fflush(stderr);               \
  } while(0);
#endif
/* Define our own assert which breaks nothing and doesn't get optimized */
#define ASSERT_EQ(message,expected,actual)                \
 do {                                                     \
  if (expected != actual) {                               \
    fprintf(stderr,                                       \
            "%s :: in %s on line %d: %s != %s"            \
            " expected %d, got %d\n",                     \
            message,                                      \
            __FILE__,                                     \
            __LINE__,                                     \
            #expected,#actual,                            \
           (int)#expected,(int)#actual);                  \
    test_failed++;                                        \
  }                                                       \
 } while (0)

/* Define our own assert which breaks nothing and doesn't get optimized */
#define ASSERT(message,expr)                              \
 do {                                                     \
  if (!(expr)) {                                          \
    fprintf(stderr,                                       \
            "%s :: in %s on line %d: %s\n",               \
            message,                                      \
            __FILE__,                                     \
            __LINE__,                                     \
            #expr);                                       \
    test_failed++;                                        \
  }                                                       \
 } while (0)

#define RED "\033[031m"
#define GREEN "\033[032m"
#define YELLOW "\033[033m"
#define NORMAL "\033[0m"

extern volatile int test_failed;

typedef struct tt_Test{
  char* name;
  void (*test)();
  struct tt_Test *next;
} tt_test;

typedef struct tt_Suite{
 tt_test *head;
 tt_test *tail;
} tt_suite;

tt_suite* tt_suite_new();
void tt_add(tt_suite* suite, char* test_name, void(*cb)());
    

int tt_run(tt_suite* suite,int argc, char** argv);

#endif
