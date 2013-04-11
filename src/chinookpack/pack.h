#ifndef chinookpack_pack_h
#define chinookpack_pack_h

// ## The packer
//
// This structure is used to pack and encode input data (int, double, raw bytes) into a /msgpack/chinookpack/ encoded format that is stored in an arbitrary data structure.
//
// To be independent of the data structure used chinookpack use a form of inversion of control (IOC) in a way that you write your own function that write the encoded data into your structure.
//

// ### chinookpack_packer_write
//
// The function prototype that is used for the inversion of control to write in your data stucture
// void* data - the data structure we want to write to
// const char* buf - the actual data we want to write
// unsigned int len - the length of *buf*
//
// Returns 0 for a success
typedef int (*chinookpack_packer_write)(void* data, const char* buf, unsigned int len);

// ### chinookpack_packer
//
// The actual packer that contains the data structure and the callback function
typedef struct chinookpack_packer {
	void* data;
	chinookpack_packer_write callback;
} chinookpack_packer;

// ### chinookpack_packer_init()
//
// The packer initialization formula
// chinookpack_packer* pk - the packer to initialize
// void* data - the data structure we wish to write to
// chinookpack_packer_write callback - the callback function used to write in your data structure
static void chinookpack_packer_init(chinookpack_packer* pk, void* data, chinookpack_packer_write callback);

// Allocation of the packer
// This is used for dynamic allocation
//
// ### chinookpack_packer* chinookpack_packer_new()
//
// void* data - the data structure we wish to write to
// chinookpack_packer_write callback - the callback function used to write in your data structure
// Returns the dynamically allocated structure 
static chinookpack_packer* chinookpack_packer_new(void* data, chinookpack_packer_write callback);

// ### chinookpack_packer_free()
//
// deallocates a dynamically allocated chinookpack_parser data sctructure
// chinookpack_packer* pk - the structure to deallocate
static void chinookpack_packer_free(chinookpack_packer* pk);


// ## The packing functions

// Nil
static int chinookpack_pack_nil(chinookpack_packer* pk);

// Boolean 
static int chinookpack_pack_true(chinookpack_packer* pk);
static int chinookpack_pack_false(chinookpack_packer* pk);

// Integer
static int chinookpack_pack_uint8(chinookpack_packer* pk, uint8_t d);
static int chinookpack_pack_uint16(chinookpack_packer* pk, uint16_t d);
static int chinookpack_pack_int8(chinookpack_packer* pk, int8_t d);
static int chinookpack_pack_int16(chinookpack_packer* pk, int16_t d);

// Float
static int chinookpack_pack_float(chinookpack_packer* pk, float d);

// Raw
static int chinookpack_pack_raw(chinookpack_packer* pk, size_t l);
static int chinookpack_pack_raw_body(chinookpack_packer* pk, const void* b, size_t l);



inline void chinookpack_packer_init(chinookpack_packer* pk, void* data, chinookpack_packer_write callback){
  pk->data = data;
  pk->callback = callback;
}

inline chinookpack_packer* chinookpack_packer_new(void* data,chinookpack_packer_write callback){
	chinookpack_packer* pk = (chinookpack_packer*)calloc(1, sizeof(chinookpack_packer));

	if(!pk) { return NULL; }
	chinookpack_packer_init(pk, data, callback);
  return pk;
}

inline void chinookpack_packer_free(chinookpack_packer* pk)
{
	free(pk);
}


// Nil
static int chinookpack_pack_nil(chinookpack_packer* pk){
  char buf[] = {0xc0};

  return pk->callback(pk->data, buf,1);
}

// Boolean 
static int chinookpack_pack_true(chinookpack_packer* pk){
  char buf[] = {0xc3};

  return pk->callback(pk->data, buf,1);
}
static int chinookpack_pack_false(chinookpack_packer* pk){
  char buf[] = {0xc2};

  return pk->callback(pk->data, buf,1);
}

static int chinookpack_pack_uint8(chinookpack_packer* pk, uint8_t d){
  char buf[2] = { 0xcc, d }; 

  return pk->callback(pk->data, buf,2);
}

static int chinookpack_pack_uint16(chinookpack_packer* pk, uint16_t d){
  char buf[3] = { 0xcd,
                  (uint8_t)((d >> 8)   & 0xff),
                  (uint8_t)( d         & 0xff) };

  return pk->callback(pk->data, buf,3);
}

static int chinookpack_pack_int8(chinookpack_packer* pk, int8_t d){
  char buf[2] = { 0xd0 , d };

  return pk->callback(pk->data, buf,2);
}

static int chinookpack_pack_int16(chinookpack_packer* pk, int16_t d){
  char buf[3] = { 0xd1,
                  ((d >> 8)   & 0xff),
                  ( d         & 0xff) };

  return pk->callback(pk->data, buf,3);
}


static int chinookpack_pack_float(chinookpack_packer* pk, float d){

  union { float f; uint32_t i; } mem;
  mem.f = d;
  char buf[5];
  buf[0] = 0xca;
  buf[1] = (mem.i >> 24) & 0xff;
  buf[2] = (mem.i >> 16) & 0xff;
  buf[3] = (mem.i >> 8 ) & 0xff;
  buf[4] = (mem.i      ) & 0xff;
  return pk->callback(pk->data, buf,5);
}

static int chinookpack_pack_raw(chinookpack_packer* pk, size_t l){
  	if(l < 32) {
    char d = 0xa0 | (uint8_t)l;
    return pk->callback(pk->data,&d,1);
	} else if(l < 65536) {
		char buf[3];
		buf[0] = 0xda;
    buf[1] = (l >> 8)  & 0xff;
    buf[2] = (l     )  & 0xff;
    return pk->callback(pk->data,buf,3);
	} else {
		char buf[5];
		buf[0] = 0xdb;
    buf[1] = (l >> 24) & 0xff;
    buf[2] = (l >> 16) & 0xff;
    buf[3] = (l >> 8 ) & 0xff;
    buf[4] = (l      ) & 0xff;
    return pk->callback(pk->data,buf,5);
	}
}
static int chinookpack_pack_raw_body(chinookpack_packer* pk, const void* b, size_t l){
  return pk->callback(pk->data,(const char*)b,l);
}

#endif
