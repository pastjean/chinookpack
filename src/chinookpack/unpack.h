#ifndef chinookpack_unpack_h
#define chinookpack_unpack_h


#include "object.h"

typedef struct chinookpackpack_unpacked {
	chinookpack_object data;
} chinookpack_unpacked;

static inline void chinookpack_unpacker_init(chinookpack_unpacked* result);
bool chinookpack_unpack_next(chinookpack_unpacked* result,
		const char* buf, size_t len, size_t* off);

static inline void chinookpack_unpacked_init(chinookpack_unpacked* result){
  result->data.type = CHINOOKPACK_OBJECT_NIL;
}

bool chinookpack_unpack_next(chinookpack_unpacked* result,
		const char* buf, size_t len, size_t* off);

#endif

