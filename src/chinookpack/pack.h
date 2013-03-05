#ifndef chinookpack_pack_h
#define chinookpack_pack_h

typedef int (*chinookpack_packer_write)(void* data, const char* buf, unsigned int len);

typedef struct chinookpack_packer {
	void* data;
	chinookpack_packer_write callback;
} chinookpack_packer;

/* static void msgpack_packer_init(msgpack_packer* pk, void* data, msgpack_packer_write callback); */

/* static msgpack_packer* msgpack_packer_new(void* data, msgpack_packer_write callback); */
/* static void msgpack_packer_free(msgpack_packer* pk); */

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


// Implementation of packer initialization functions
/* inline void msgpack_packer_init(msgpack_packer* pk, void* data, msgpack_packer_write callback) */
/* { */
/* 	pk->data = data; */
/* 	pk->callback = callback; */
/* } */

/* inline msgpack_packer* msgpack_packer_new(void* data, msgpack_packer_write callback) */
/* { */
/* 	msgpack_packer* pk = (msgpack_packer*)calloc(1, sizeof(msgpack_packer)); */
/* 	if(!pk) { return NULL; } */
/* 	msgpack_packer_init(pk, data, callback); */
/* 	return pk; */
/* } */

/* inline void msgpack_packer_free(msgpack_packer* pk) */
/* { */
/* 	free(pk); */
/* } */
#endif
