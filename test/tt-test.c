#include "tt-test.h"

volatile int test_failed=0;

tt_suite* tt_suite_new(){
  tt_suite* suite = malloc(sizeof(tt_suite));

  suite->head = NULL;
  suite->tail = NULL;
  
  return suite;
}

void tt_add(tt_suite* suite, char* test_name, void(*cb)()){
  tt_test *test = malloc(sizeof(tt_test));

  test->name = malloc((strlen(test_name)+1)* sizeof(char));
  strcpy(test->name,test_name);

  test->test = cb;
  test->next = NULL;

  if(suite->head == NULL){
    suite->head = test;
    suite->tail = test;
  }else{
    suite->tail->next = test;
    suite->tail = test;
  }

}

int tt_run(tt_suite* suite,int argc, char** argv){
  int total  = 0,
      passed = 0,
      failed = 0;

  for(tt_test* t = suite->head;  t != NULL; t = t->next){
    total++;
    test_failed = 0;

    printf("Running: %s ", t->name);
    t->test();

    if(test_failed){
      failed++;
      printf("%sx%s\n",RED,NORMAL);
    }else{
      passed++;
      printf("%so%s\n",GREEN,NORMAL);
    }
  }

  char* cpassed = passed > 0 ? GREEN : NORMAL;
  char* cfailed = failed > 0 ? RED   : NORMAL;
  printf("Test run \n"\
         "total: %i, %spassed: %i, %sfailed: %i %s\n",total,cpassed,passed,cfailed,failed,NORMAL);

  return failed != 0;
}
