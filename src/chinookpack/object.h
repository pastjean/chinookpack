#ifndef chinookpack_object_h
#define chinookpack_object_h

typedef enum {
  CHINOOKPACK_OBJECT_NIL,
  CHINOOKPACK_OBJECT_BOOLEAN,
  CHINOOKPACK_OBJECT_UINT8,
  CHINOOKPACK_OBJECT_UINT16,
  CHINOOKPACK_OBJECT_INT8,
  CHINOOKPACK_OBJECT_INT16,
  CHINOOKPACK_OBJECT_FLOAT,
  CHINOOKPACK_OBJECT_RAW,
} chinookpack_object_type;

typedef struct {
  uint32_t size;
  const char* ptr;
} chinookpack_object_raw;

typedef union {
  bool boolean;
  uint64_t u64;
  int64_t  i64;
  double   dec;
  chinookpack_object_raw raw;
} chinookpack_object_union;

typedef struct chinookpack_object {
  chinookpack_object_type type;
  chinookpack_object_union via;
} chinookpack_object;

#endif

