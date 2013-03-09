#ifndef chinookpack_fbuffer_h
#define chinookpack_fbuffer_h

// Implementation of a fixed size buffer which use a static array to work,
// everything is inline for performance.
// 
// Usage : 
//
//     // Initialize it
//     char dataKeeper[15];
//     chinookpack_fbuffer buf;
//     chinookpack_fbuffer_init(&buf,dataKeeper,15);
//
//     // Then you can write to it
//     chinookpack_fbuffer_write(buf,"DATATOWRITE",strlen("DATATOWRITE"))
//
//     // And empty it before refilling it
//     chinookpack_fbuffer_clear(buf);
//

typedef struct chinookpack_fbuffer {
	size_t size;
  size_t used;
	char* data;
} chinookpack_fbuffer;

static inline void chinookpack_fbuffer_init(chinookpack_fbuffer* fbuf, char* dat_ary, size_t size)
{
  fbuf->data = dat_ary;
  fbuf->size = size;
  fbuf->used = 0;
}

static inline int chinookpack_fbuffer_write(void* data, const char* buf, unsigned int len)
{
	chinookpack_fbuffer* fbuf = (chinookpack_fbuffer*)data;

  if(len > (fbuf->size-fbuf->used)) {return -1;}

  fbuf->size += len;
  memcpy(fbuf->data + fbuf->size,buf,len);
	return 0;
}


static inline void chinookpack_fbuffer_clear(chinookpack_fbuffer* fbuf)
{
	fbuf->used = 0;
}


#endif
