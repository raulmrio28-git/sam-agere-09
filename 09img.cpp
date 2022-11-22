/* //===========================================================\\
   || 09 Image Utilities Code - 09img.cpp                       ||
   ||-----------------------------------------------------------||
   || 0.3 = 22 Nov. 2022 - Use array pointers instead of file as||
   || input and vector as output                                ||
   || 0.2 = 16 Aug. 2022 - Now use bit field for type (RLE, off-||
   || set)                                                      ||
   || 0.1 = 18 July 2022 - Implementing decode function         ||
   \\===========================================================// */

#include <iostream>
#include "09img.h"

int img09_decode (unsigned char *in, unsigned short *out, int size) {
	int outsize = 0;
	unsigned char header, startoffset, info, bit_offset;
	unsigned short *palettebank;
	unsigned short pixel;
	unsigned char *inend = in + size;
	header = *in++;
	if (header != 0x09 && header != 0x4f && header != 0x3b) {
		printf("Invalid image\n");
		return 2;
	}
	startoffset = *in++;
	palettebank = (unsigned short*)malloc(startoffset*2);
	memcpy(palettebank, in, startoffset*2);
	in += startoffset*2;
	while(in < inend){
		info = *in++;
		if (info & IS_RLE) {	
			if (info & USES_OFFSET_BYTE) {
				bit_offset = *in++;
				pixel = palettebank[bit_offset];
			}
			else
			{
				pixel = *(unsigned short*)in;
				in+=2;
			}
			for (int a = 0; a < (info & COUNT_MAX); a++)
			{
				out[outsize] = pixel;
				outsize++;
			}
		} else {
			for (int a = 0; a < (info & COUNT_MAX); a++) {
				if (info & USES_OFFSET_BYTE) {
					bit_offset = *in++;
					pixel = palettebank[bit_offset];
				}
				else
				{
					pixel = *(unsigned short*)in;
					in+=2;
				}
				out[outsize] = pixel;
				outsize++;
			}
		}
	}

	return 0;
}