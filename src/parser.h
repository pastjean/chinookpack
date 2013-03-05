#ifndef chinookpack_parser_h
#define chinookpack_parser_h

#include <sys/types.h>

typedef enum{
  tbool,
  tuint8,
  tuint16,
  tint8,
  tint16,
  tfloat,
  traw,
} chinookpack_types;

typedef struct chinookpack_parser {
  chinookpack_types pack_type;
  int pack_data;
  uint8 pack_data_length;

} chinookpack_parser;

int chinookpack_parser_init(chinookpack_parser *parser);
int chinookpack_parser_finish(chinookpack_parser *parser);
int chinookpack_parser_has_error(chinookpack_parser *parser);
int chinookpack_parser_is_finished(chinookpack_parser *parser);
size_t chinookpack_parser_execute(chinookpack_parser *parser, const char* data,
                                 size_t len);

void** typestable[]{
  {}
  0
}

#endif
