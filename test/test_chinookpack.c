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
  char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT_EQ("Packing a nil should succeed",0, chinookpack_pack_nil(&pk));
  ASSERT_EQ("There should be an encoded nil in the data", (char)0xc0, data[0]);
}
// Boolean 
void test_pack_true(){
  char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT_EQ("Packing a true should succeed",0,chinookpack_pack_true(&pk));
  ASSERT_EQ("There should be an encoded true in the data", (char)0xc3, data[0]);
}
void test_pack_false(){
  char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT_EQ("Packing a false should succeed",0,chinookpack_pack_false(&pk));
  ASSERT_EQ("There should be an encoded false in the data", (char)0xc2, data[0]);
}

// Integer
void test_pack_uint8(){
  char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  // On test avec min et max de uint8
  ASSERT("uint8 : packing should succeed",0==chinookpack_pack_uint8(&pk,0x00));
  ASSERT_EQ("uint8 : type header", (char)0xcc, data[0]);
  ASSERT_EQ("uint8 : content", (char)0x00, data[1]);

  ASSERT("uint8 : packing should succeed",0==chinookpack_pack_uint8(&pk,0xFF));
  ASSERT_EQ("uint8 : type header", (char)0xcc, data[0]);
  ASSERT_EQ("uint8 : content", (char)0xFF, data[1]);
}
void test_pack_uint16(){
  char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  // On test avec min et max de uint8
  ASSERT("uint16 : packing should succeed",0==chinookpack_pack_uint16(&pk,0x00));
  ASSERT_EQ("uint16 : type header", (char)0xcd, data[0]);
  ASSERT_EQ("uint16 : content", (char)0x00, data[1]);
  ASSERT_EQ("uint16 : content", (char)0x00, data[2]);

  ASSERT("uint16 : packing should succeed",0==chinookpack_pack_uint16(&pk,0xFFFF));
  ASSERT_EQ("uint16 : type header", (char)0xcd, data[0]);
  ASSERT_EQ("uint16 : content", (char)0xFF, data[1]);
  ASSERT_EQ("uint16 : content", (char)0xFF, data[2]);
}
void test_pack_int8(){
  char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  // On test avec min et max de uint8
  ASSERT("int8 : packing should succeed",0==chinookpack_pack_int8(&pk,127));
  ASSERT_EQ("int8 : type header", (char)0xd0, data[0]);
  ASSERT_EQ("int8 : content", (char)127, data[1]);

  ASSERT("int8 : packing should succeed",0==chinookpack_pack_int8(&pk,-128));
  ASSERT_EQ("int8 : type header", (char)0xd0, data[0]);
  ASSERT_EQ("int8 : content", (char)(256-128), data[1]);

  ASSERT("int8 : packing should succeed",0==chinookpack_pack_int8(&pk,-1));
  ASSERT_EQ("int8 : type header", (char)0xd0, data[0]);
  ASSERT_EQ("int8 : content", (char)(256-1), data[1]);
}
void test_pack_int16(){
  ASSERT("Not implemented",0!=0);
}

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
  tt_add(suite,"uint8 packing",&test_pack_uint8);
  tt_add(suite,"uint16 packing",&test_pack_uint16);
  tt_add(suite,"int8 packing",&test_pack_int8);
  tt_add(suite,"int16 packing",&test_pack_int16);
  
  return tt_run(suite,argc,argv);
}
