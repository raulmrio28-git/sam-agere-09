/* //===========================================================\\
   || 09 Image Utilities Header - 09img.h                       ||
   ||-----------------------------------------------------------||
   || 0.3 = 22 Nov. 2022 - Use array pointers instead of file as||
   || input and vector as output                                ||
   || 0.2 = 16 Aug. 2022 - Now use bit field for type (RLE, off-||
   || set)                                                      ||
   || 0.1 = 18 July 2022 - Implementing decode function         ||
   \\===========================================================// */

#define IS_RLE 0x80 //10000000b
#define USES_OFFSET_BYTE 0x40 //01000000b
#define COUNT_MAX 0x3f //00111111b

int img09_decode (unsigned char *in, unsigned short *out, int size);