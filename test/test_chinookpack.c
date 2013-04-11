#include "tt-test.h"
#include <stdio.h>

#include <chinookpack.h>
#include <float.h>
#include <limits.h>
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
  unsigned char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT_EQ("Packing a nil should succeed",0, chinookpack_pack_nil(&pk));
  ASSERT_EQ("There should be an encoded nil in the data", (unsigned char)0xc0, data[0]);
}
// Boolean 
void test_pack_true(){
  unsigned char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT_EQ("Packing a true should succeed",0,chinookpack_pack_true(&pk));
  ASSERT_EQ("There should be an encoded true in the data", (uint8_t)0xc3, data[0]);
}
void test_pack_false(){
  unsigned char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT_EQ("Packing a false should succeed",0,chinookpack_pack_false(&pk));
  ASSERT_EQ("There should be an encoded false in the data", (uint8_t)0xc2, data[0]);
}

// Integer
void test_pack_uint8(){
  unsigned char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  // On test avec min et max de uint8
  ASSERT("uint8 : packing should succeed",0==chinookpack_pack_uint8(&pk,0x00));
  ASSERT_EQ("uint8 : type header", (uint8_t)0xcc, data[0]);
  ASSERT_EQ("uint8 : content", (uint8_t)0x00, data[1]);

  ASSERT("uint8 : packing should succeed",0==chinookpack_pack_uint8(&pk,0xFF));
  ASSERT_EQ("uint8 : type header", (uint8_t)0xcc, data[0]);
  ASSERT_EQ("uint8 : content", (uint8_t)0xFF, data[1]);
}
void test_pack_uint16(){
  unsigned char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT("uint16 : packing should succeed",0==chinookpack_pack_uint16(&pk,0x00));
  ASSERT_EQ("uint16 : type header", (uint8_t)0xcd, data[0]);
  ASSERT_EQ("uint16 : content", (uint8_t)0x00, data[1]);
  ASSERT_EQ("uint16 : content", (uint8_t)0x00, data[2]);

  ASSERT("uint16 : packing should succeed",0==chinookpack_pack_uint16(&pk,0xFFFF));
  ASSERT_EQ("uint16 : type header", (uint8_t)0xcd, data[0]);
  ASSERT_EQ("uint16 : content", (uint8_t)0xFF, data[1]);
  ASSERT_EQ("uint16 : content", (uint8_t)0xFF, data[2]);
}
void test_pack_int8(){
  unsigned char data[10];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT("int8 : packing should succeed",0==chinookpack_pack_int8(&pk,127));
  ASSERT_EQ("int8 : type header", (uint8_t)0xd0, data[0]);
  ASSERT_EQ("int8 : content", (uint8_t)127, data[1]);

  ASSERT("int8 : packing should succeed",0==chinookpack_pack_int8(&pk,-128));
  ASSERT_EQ("int8 : type header", (uint8_t)0xd0, data[0]);
  ASSERT_EQ("int8 : content", (uint8_t)(256-128), data[1]);

  ASSERT("int8 : packing should succeed",0==chinookpack_pack_int8(&pk,-1));
  ASSERT_EQ("int8 : type header", (uint8_t)0xd0, data[0]);
  ASSERT_EQ("int8 : content", (uint8_t)(256-1), data[1]);
}
void test_pack_int16(){
  char data[10];
  char answerParts[2];
  chinookpack_packer pk;
  chinookpack_packer_init(&pk, data, array_10_write);

  ASSERT("int16 : packing should succeed",0==chinookpack_pack_int16(&pk,32767));
  ASSERT_EQ("int16 : type header", (char)0xd1, data[0]);
  answerParts[0]= (32767 >> 8) & 0xff;
  answerParts[1]= 32767 & 0xff;
  ASSERT_EQ("int16 : content", answerParts[0], data[1]);
  ASSERT_EQ("int16 : content", answerParts[1], data[2]);

  ASSERT("int16 : packing should succeed",0==chinookpack_pack_int16(&pk,-32768));
  ASSERT_EQ("int16 : type header", (char)0xd1, data[0]);
  answerParts[0]= ((65536-32768) >> 8) & 0xff;
  answerParts[1]= (65536-32768) & 0xff;
  ASSERT_EQ("int16 : content", answerParts[0], data[1]);
  ASSERT_EQ("int16 : content", answerParts[1], data[2]);

  ASSERT("int16 : packing should succeed",0==chinookpack_pack_int16(&pk,-1));
  ASSERT_EQ("int16 : type header", (char)0xd1, data[0]);
  answerParts[0]= ((65536-1) >> 8) & 0xff;
  answerParts[1]= (65536-1) & 0xff;
  ASSERT_EQ("int16 : content", answerParts[0], data[1]);
  ASSERT_EQ("int16 : content", answerParts[1], data[2]);
}

/* // Float */
void test_pack_float(){
  union { float f; uint32_t i; } mem;
  char data[10];
  chinookpack_fbuffer fbuf;
  chinookpack_packer pk;
  chinookpack_fbuffer_init(&fbuf,data,10);
  chinookpack_packer_init(&pk, data, array_10_write);


  int testDataLength = 7;
  float testData[] = {0.0, 1.0, -1.0, FLT_MIN, FLT_MAX , 1.0/0.0 , -(1.0/0.0)};
 
  for(int i = 0; i < testDataLength; i++){
    chinookpack_fbuffer_clear(&fbuf);
    mem.f=testData[i];
    ASSERT("float : packing should succeed",0==chinookpack_pack_float(&pk,testData[i]));
    ASSERT_EQ("float : type header", (int8_t)0xca, data[0]);
    ASSERT_EQ("float : part 1",(int8_t)(mem.i >> 24 & 0xff), data[1]);
    ASSERT_EQ("float : part 1",(int8_t)(mem.i >> 16 & 0xff), data[2]);
    ASSERT_EQ("float : part 1",(int8_t)(mem.i >> 8  & 0xff), data[3]);
    ASSERT_EQ("float : part 1",(int8_t)(mem.i       & 0xff), data[4]);
  }
}

void test_pack_raw(){
  char data[10];
  
  chinookpack_fbuffer fbuf;
  chinookpack_packer pk;
  chinookpack_fbuffer_init(&fbuf,data,10);
  chinookpack_packer_init(&pk, &fbuf, chinookpack_fbuffer_write);

  ASSERT("raw : packing should succeed",0==chinookpack_pack_raw(&pk,3));
  ASSERT_EQ("raw : type header", (int8_t)0xa3, data[0]);
  ASSERT("raw body : packing should succeed",0==chinookpack_pack_raw_body(&pk,"abc",3));
  ASSERT("raw body : data packing",0==strncmp("abc",&(data[1]),3));
  //ASSERT("raw : test unimplemented",0);
}


void test_fbuffer(){

  char data[10];
  char* equal = "abc";
  chinookpack_fbuffer fbuf;
  chinookpack_fbuffer_init(&fbuf,data,10);

  chinookpack_fbuffer_write(&fbuf,"abc",3);
  chinookpack_fbuffer_write(&fbuf,"abc",3);


  for(int i=0;i<6;i++){
    ASSERT_EQ("data",data[i],equal[i%3]);
  }
}

// The runner
int main(int argc,char** argv){
  tt_suite* suite = tt_suite_new();

  tt_add(suite,"self-test",&selftest);
  tt_add(suite,"test-failure",&test_failure);

  // Add your test functions here
  tt_add(suite,"test packer structure",&test_packer);
  tt_add(suite,"test fbuffer",&test_fbuffer);
  tt_add(suite,"nil packing",&test_pack_nil);
  tt_add(suite,"true packing",&test_pack_true);
  tt_add(suite,"false packing",&test_pack_false);
  tt_add(suite,"uint8 packing",&test_pack_uint8);
  tt_add(suite,"uint16 packing",&test_pack_uint16);
  tt_add(suite,"int8 packing",&test_pack_int8);
  tt_add(suite,"int16 packing",&test_pack_int16);
  tt_add(suite,"float packing",&test_pack_float);
  tt_add(suite,"raw packing",&test_pack_raw);
  
  return tt_run(suite,argc,argv);
}
