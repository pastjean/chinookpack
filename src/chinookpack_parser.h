#ifndef chinookpack_parser_h
#define chinookpack_parser_h

#include <sys/types.h>

typedef struct chinookpack_parser {
  // 11 bits = 2048 ids
  //
  // Each element has a different id for different actions which is defined in
  // a table
  int can_id;
  // 4 bits
  int can_length;

  int pack_type;
  int pack_data;

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
