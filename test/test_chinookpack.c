#include "tt-test.h"
#include <stdio.h>

#include <chinookpack.h>
// Define test functions HEREEEEE
//extern void test_config();


// This is the test library self test
// To be assured of the test library working let it there
void selftest(){
  ASSERT("1 should equal 1",1==1);

}

void test_failure(){
  ASSERT("fail please",1==0);
  // This test should fail, so test the failure
  
  if(test_failed==1)
    test_failed=0;
  else
    test_failed=1;
}

void test_pack_library(){
  // Initialize packer
  // Initialize buffer
  // Pack things
}


// Nil
void test_pack_nil(){
  chinookpack_packer pk;

  ASSERT("Packing a nil should succed",0==chinookpack_pack_nil(&pk));
}
// Boolean 
void test_pack_true(){
  chinookpack_packer pk;

  chinookpack_pack_true(&pk);
  ASSERT("asd",0!=0);
}
void test_pack_false(){
  chinookpack_packer pk;
  chinookpack_pack_false(&pk);
  ASSERT("asd",0!=0);
}
// Integer
void test_pack_uint8(){
  chinookpack_packer pk;

  // On test avec min et max de uint8
  chinookpack_pack_uint8(&pk, 8);
  ASSERT("asd",0!=0);
}
void test_pack_uint16(){
  chinookpack_packer pk;

  chinookpack_pack_uint16(&pk, 8);
  ASSERT("asd",0!=0);
}
void test_pack_int8(){
  chinookpack_packer pk;

  chinookpack_pack_int8(&pk, -8);
  ASSERT("asd",0!=0);
}
void test_pack_int16(){
  chinookpack_packer pk;

  chinookpack_pack_int16(&pk, -8);
  ASSERT("asd",0!=0);
}

// Float
void test_pack_float(){
  chinookpack_packer pk;

  chinookpack_pack_float(&pk, 8.0);
  ASSERT("asd",0!=0);
}

void test_pack_raw(){
  chinookpack_packer pk;

  chinookpack_pack_raw(&pk, 3);
  chinookpack_pack_raw_body(&pk, "abc", 3);
  ASSERT("asd",0!=0);
}

// Nil




// Raw

// The runner
int main(int argc,char** argv){
  tt_suite* suite = tt_suite_new();

  tt_add(suite,"self-test",&selftest);
  tt_add(suite,"test-failure",&test_failure);

  // Add your test functions here
  tt_add(suite,"nil packing",&test_pack_nil);
  
  return tt_run(suite,argc,argv);
}
