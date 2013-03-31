#ifndef chinookpack_object_h
#define chinookpack_object_h

typedef enum {
  NIL              = 0x00,
  BOOLEAN          = 0x01,
  POSITIVE_INTEGER = 0x02,
  NEGATIVE_INTEGER = 0x03,
  DOUBLE           = 0x04,
  RAW              = 0x05,
} chinookpack_object_type;

#define CHINOOKPACK_OBJECT_NIL              chinookpack_object_type.NIL
#define CHINOOKPACK_OBJECT_BOOLEAN          chinookpack_object_type.BOOLEAN
#define CHINOOKPACK_OBJECT_POSITIVE_INTEGER chinookpack_object_type.POSITIVE_INTEGER
#define CHINOOKPACK_OBJECT_NEGATIVE_INTEGER chinookpack_object_type.NEGATIVE_INTEGER
#define CHINOOKPACK_OBJECT_DOUBLE           chinookpack_object_type.DOUBLE
#define CHINOOKPACK_OBJECT_RAW              chinookpack_object_type.RAW

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


void chinookpack_object_print(FILE* out, chinookpack_object o);

#endif

