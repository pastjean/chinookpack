#include "chinookpack/object.h"

void chinookpack_object_print(FILE* out, chinookpack_object o)
{
	switch(o.type) {
	case CHINOOKPACK_OBJECT_NIL:
		fprintf(out, "nil");
		break;

	case CHINOOKPACK_OBJECT_BOOLEAN:
		fprintf(out, (o.via.boolean ? "true" : "false"));
		break;

	case CHINOOKPACK_OBJECT_POSITIVE_INTEGER:
		fprintf(out, "%"PRIu64, o.via.u64);
		break;

	case CHINOOKPACK_OBJECT_NEGATIVE_INTEGER:
		fprintf(out, "%"PRIi64, o.via.i64);
		break;

	case CHINOOKPACK_OBJECT_DOUBLE:
		fprintf(out, "%f", o.via.dec);
		break;

	case CHINOOKPACK_OBJECT_RAW:
		fprintf(out, "\"");
		fwrite(o.via.raw.ptr, o.via.raw.size, 1, out);
		fprintf(out, "\"");
		break;

	default:
		// FIXME
		fprintf(out, "#<UNKNOWN %i %"PRIu64">", o.type, o.via.u64);
	}
}

