/* //===========================================================\\
   || 09 Image Utilities Code - 09img.cpp                       ||
   ||-----------------------------------------------------------||
   || 0.2 = 16 Aug. 2022 - Now use bit field for type (RLE, off-||
   || set)                                                      ||
   || 0.1 = 18 July 2022 - Implementing decode function         ||
   \\===========================================================// */

#include <iostream>
#include <fstream>
#include <vector>
#include "09img.h"

int img09_decode (std::ifstream &file, std::vector<unsigned short>& out) {
	unsigned char header, startoffset, info, bit_offset;
	unsigned short pixel;
	file.read((char*)&header, 1);
	if (header != 0x09 && header != 0x4f && header != 0x3b) {
		printf("Invalid image\n");
		return 2;
	}
	file.read((char*)&startoffset, 1);
	file.seekg((startoffset * 2) + 2);

	while(!file.eof()){
		file.read((char*)&info, 1);
		int old_pos;
		if (info & IS_RLE) {	
			if (info & USES_OFFSET_BYTE) {
				file.read((char*)&bit_offset, 1);
				int data_offset = 2 + (bit_offset*2);
				old_pos = (int)file.tellg();
				file.seekg(data_offset);
			}
				file.read((char*)&pixel, 2);
			if (info & USES_OFFSET_BYTE) {
				file.seekg(old_pos);
			}
			for (int a=0; a < (info & COUNT_MAX); a++) {
				out.push_back(pixel);
			}
		} else {
			for (int a=0; a < (info & COUNT_MAX); a++) {
				if (info & USES_OFFSET_BYTE) {
					file.read((char*)&bit_offset, 1);
					int data_offset = 2 + (bit_offset*2);
					old_pos = (int)file.tellg();
					file.seekg(data_offset);
				}
					file.read((char*)&pixel, 2);
				if (info & USES_OFFSET_BYTE) {
					file.seekg(old_pos);
				} 
				out.push_back(pixel);
			}
		}
	}

	return 0;
}