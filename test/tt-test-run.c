#include "tt-test.h"
#include <stdio.h>


// Define test functions HEREEEEE
//extern void test_config();


// This is the test library self test
void selftest(){
  ASSERT("MESSGE",1==1);

}

void test_failure(){
  ASSERT("This should have failed",1==0);
  // This test should fail, so test the failure
  if(test_failed==1)
    test_failed=0;
  else
    test_failed=1;
}


// The runner
int main(int argc,char** argv){
  tt_suite* suite = tt_new_suite();

  tt_add(suite,"self-test",&selftest);
  tt_add(suite,"test-failure",&test_failure);

  // Add your test functions here

  return tt_run(suite,argc,argv);
}
