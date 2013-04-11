#ifndef chinookpack_unpack_h
#define chinookpack_unpack_h

#include <sysdep.h>
#include <chinookpack/object.h>

typedef struct chinookpackpack_unpacked {
	chinookpack_object data;
} chinookpack_unpacked;

static inline void chinookpack_unpacked_init(chinookpack_unpacked* result){
  result->data.type = CHINOOKPACK_OBJECT_NIL;
}

// chinookpack_unpack_next
//
// unpack the buf next object in `buf` from `off`
//
// result : the result of the unpacking goes in there
// buf    : a `c` array buffer containing the data to unpack
// len    : the length of the `buf`, prevents overflows
// off    : the place to start unpacking in `buf`, usefull for multiple unpacks
//
// return if the unpacking succeded

bool chinookpack_unpack_next(chinookpack_unpacked* result,
		const char* buf, size_t len, size_t* off);

#endif

