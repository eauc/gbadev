#include <object.h>

object_attribute_t const OBJECT_ATTRIBUTE_INIT = {0,
						  MODE_DISABLE,
						  GFX_MODE_NORMAL,
						  FALSE,
						  PALETTE_4BPP,
						  SHAPE_SQUARE,
						  0,
						  FALSE,
						  FALSE,
						  SIZE_8,
						  0,
						  0,
						  0};

void object_init(object_block_t buffer,
		 u32 buffer_size) {

  object_attrblock_pt l_buffer = (object_attrblock_pt)buffer;
  u32 count = 0;

  for(count = 0 ;
      count < buffer_size ;
      count++) {

    l_buffer[count] = OBJECT_ATTRIBUTE_INIT;

  }

}

void object_copy(object_block_t dst,
		 object_block_t src,
		 u32 src_size) {

  u32 count = 0;

  for(count = 0 ;
      count < src_size ;
      count++) {
      
    dst[count] = src[count];

  }

}

