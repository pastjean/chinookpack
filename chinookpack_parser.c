#include "chinookpack_parser.h"



int chinookpack_parser_init(chinookpack_parser *parser){
	int cs = 0;
	parser->cs= cs;
	parser->can_id=0;
	parser->can_length=0;
    parser->pack_type=0;
    parser->pack_data=0;

	return(1);
}

size_t chinookpack_parser_execute(chinookpack_parser *parser, const char* data,
                                 size_t length){
 return 0;
}


int chinookpack_parser_finish(chinookpack_parser *parser){
  if (chinookpack_parser_has_error(parser) ) {
    return -1;
  } else if (chinookpack_parser_is_finished(parser) ) {
    return 1;
  } else {
    return 0;
  }
}


int chinookpack_parser_has_error(chinookpack_parser *parser){
//	return parser->cs == chinookpack_parser_error;
	return 0;
}
int chinookpack_parser_is_finished(chinookpack_parser *parser){
//	return parser->cs >= chinookpack_parser_first_final;
	return 1;
}
