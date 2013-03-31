#include "chinookpack/unpack.h"


static inline int callback_uint8(unpack_user* u, uint8_t d, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_POSITIVE_INTEGER; o->via.u64 = d; return 0; }

static inline int callback_uint16(unpack_user* u, uint16_t d, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_POSITIVE_INTEGER; o->via.u64 = d; return 0; }

static inline int callback_uint32(unpack_user* u, uint32_t d, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_POSITIVE_INTEGER; o->via.u64 = d; return 0; }

static inline int callback_uint64(unpack_user* u, uint64_t d, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_POSITIVE_INTEGER; o->via.u64 = d; return 0; }

static inline int callback_int8(unpack_user* u, int8_t d, msgpack_object* o)
{ if(d >= 0) { o->type = MSGPACK_OBJECT_POSITIVE_INTEGER; o->via.u64 = d; return 0; }
		else { o->type = MSGPACK_OBJECT_NEGATIVE_INTEGER; o->via.i64 = d; return 0; } }

static inline int callback_int16(unpack_user* u, int16_t d, msgpack_object* o)
{ if(d >= 0) { o->type = MSGPACK_OBJECT_POSITIVE_INTEGER; o->via.u64 = d; return 0; }
		else { o->type = MSGPACK_OBJECT_NEGATIVE_INTEGER; o->via.i64 = d; return 0; } }

static inline int callback_int32(unpack_user* u, int32_t d, msgpack_object* o)
{ if(d >= 0) { o->type = MSGPACK_OBJECT_POSITIVE_INTEGER; o->via.u64 = d; return 0; }
		else { o->type = MSGPACK_OBJECT_NEGATIVE_INTEGER; o->via.i64 = d; return 0; } }

static inline int callback_int64(unpack_user* u, int64_t d, msgpack_object* o)
{ if(d >= 0) { o->type = MSGPACK_OBJECT_POSITIVE_INTEGER; o->via.u64 = d; return 0; }
		else { o->type = MSGPACK_OBJECT_NEGATIVE_INTEGER; o->via.i64 = d; return 0; } }

static inline int callback_float(unpack_user* u, float d, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_DOUBLE; o->via.dec = d; return 0; }

static inline int callback_double(unpack_user* u, double d, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_DOUBLE; o->via.dec = d; return 0; }

static inline int callback_nil(unpack_user* u, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_NIL; return 0; }

static inline int callback_true(unpack_user* u, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_BOOLEAN; o->via.boolean = true; return 0; }

static inline int callback_false(unpack_user* u, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_BOOLEAN; o->via.boolean = false; return 0; }

static inline int callback_raw(unpack_user* u, const char* b, const char* p, unsigned int l, msgpack_object* o)
{
	o->type = MSGPACK_OBJECT_RAW;
	o->via.raw.ptr = p;
	o->via.raw.size = l;
	u->referenced = true;
	return 0;
}

