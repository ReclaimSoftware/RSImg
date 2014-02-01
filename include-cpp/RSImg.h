#ifndef __RSImg_h__
#define __RSImg_h__

#include <stdint.h>
#include <stdio.h>

extern "C" int RSImgFreadPPMP6Header(FILE *file, uint32_t *width, uint32_t *height, uint32_t *headerSize);

#endif
