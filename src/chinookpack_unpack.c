#include "chinookpack/unpack.h"

static inline int callback_nil(unpack_user* u, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_NIL; return 0; }

static inline int callback_true(unpack_user* u, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_BOOLEAN; o->via.boolean = true; return 0; }

static inline int callback_false(unpack_user* u, msgpack_object* o)
{ o->type = MSGPACK_OBJECT_BOOLEAN; o->via.boolean = false; return 0; }

bool chinookpack_unpack_next(chinookpack_unpacked* result,
		const char* buf, size_t len, size_t* off);{

	size_t noff = 0;
	if(off != NULL) { noff = *off; }


	if(len <= noff) {
		return false;
	}

  // TODO: DO SHITS HERE

	if(off != NULL) { *off = noff; }
  return true;
}
