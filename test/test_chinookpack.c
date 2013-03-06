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

// mock function
int array_10_write(void* data, const char* buf, unsigned int len){
  if(len > 10){return -1;}

  memcpy(data,buf,len);
  return 0;
}

void test_packer(){
  char* to_write= "Hello";
  int data[10];
  // Preallocated packer
  chinookpack_packer pk1;

  chinookpack_packer_init(&pk1, data, array_10_write);
  pk1.callback(pk1.data,to_write, strlen(to_write)); 
  
  ASSERT("static: written data should be the same has original",
         0==strncmp(pk1.data,to_write,strlen(to_write)));

  // Dynamic allocation test
  int data2[10];
  chinookpack_packer *pk2 = chinookpack_packer_new(data2,array_10_write);
  
  pk2->callback(pk2->data,to_write,strlen(to_write)); 

  ASSERT("dynamic: written data should be the same has original",
         0==strncmp(pk1.data,to_write,strlen(to_write)));
  chinookpack_packer_free(pk2);
}

// Nil
void test_pack_nil(){
  int data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT("Packing a nil should succeed",0==chinookpack_pack_nil(&pk));
  int* output = (int*) pk.data;
  ASSERT("There should be an encoded nil in the data", 0xc0 ==output[0]);
}
// Boolean 
void test_pack_true(){
  int data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT("Packing a true should succeed",0==chinookpack_pack_true(&pk));
  int* output = (int*) pk.data;
  ASSERT("There should be an encoded true in the data", 0xc3 == output[0]);
}
void test_pack_false(){
  int data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT("Packing a false should succeed",0==chinookpack_pack_false(&pk));
  int* output = (int*) pk.data;
  ASSERT("There should be an encoded false in the data", 0xc2 == output[0]);
}
/* // Integer */
/* void test_pack_uint8(){ */
/*   chinookpack_packer pk; */

/*   // On test avec min et max de uint8 */
/*   chinookpack_pack_uint8(&pk, 8); */
/*   ASSERT("asd",0!=0); */
/* } */
/* void test_pack_uint16(){ */
/*   chinookpack_packer pk; */

/*   chinookpack_pack_uint16(&pk, 8); */
/*   ASSERT("asd",0!=0); */
/* } */
/* void test_pack_int8(){ */
/*   chinookpack_packer pk; */

/*   chinookpack_pack_int8(&pk, -8); */
/*   ASSERT("asd",0!=0); */
/* } */
/* void test_pack_int16(){ */
/*   chinookpack_packer pk; */

/*   chinookpack_pack_int16(&pk, -8); */
/*   ASSERT("asd",0!=0); */
/* } */

/* // Float */
/* void test_pack_float(){ */
/*   chinookpack_packer pk; */

/*   chinookpack_pack_float(&pk, 8.0); */
/*   ASSERT("asd",0!=0); */
/* } */

/* void test_pack_raw(){ */
/*   chinookpack_packer pk; */

/*   chinookpack_pack_raw(&pk, 3); */
/*   chinookpack_pack_raw_body(&pk, "abc", 3); */
/*   ASSERT("asd",0!=0); */
/* } */

// Nil




// Raw

// The runner
int main(int argc,char** argv){
  tt_suite* suite = tt_suite_new();

  tt_add(suite,"self-test",&selftest);
  tt_add(suite,"test-failure",&test_failure);

  // Add your test functions here
  tt_add(suite,"test packer structure",&test_packer);
  tt_add(suite,"nil packing",&test_pack_nil);
  tt_add(suite,"true packing",&test_pack_true);
  tt_add(suite,"false packing",&test_pack_false);
  
  return tt_run(suite,argc,argv);
}
