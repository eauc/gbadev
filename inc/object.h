#ifndef OBJECT_H_
#define OBJECT_H_

#include <types.h>
#include <mem.h>

enum {

  MODE_NORMAL        = 0x00,
  MODE_AFFINE        = 0x01,
  MODE_DISABLE       = 0x02,
  MODE_AFFINE_DOUBLE = 0x03

};

enum {

  GFX_MODE_NORMAL         = 0x00,
  GFX_MODE_ALPHA_BLENDING = 0x01,
  GFX_MODE_WINDOW         = 0x10,
  GFX_MODE_FORBIDDEN      = 0x11

};

enum {

  PALETTE_4BPP = 0,
  PALETTE_8BPP = 1

};

enum {

  SHAPE_SQUARE = 0x00,
  SHAPE_WIDE   = 0x01,
  SHAPE_TALL   = 0x10

};

enum {

  SIZE_8  = 0x00,
  SIZE_16 = 0x01,
  SIZE_32 = 0x10,
  SIZE_64 = 0x11

};

typedef u32 object_t[2];

typedef struct object_attribute_tag {

  /* ATTR 0 */
  u32 Y:8;
  u32 mode:2;
  u32 gfx_mode:2;
  u32 enable_mosaic:1;
  u32 palette_bpp:1;
  u32 shape:2;
  /* ATTR 1 */
  u32 X:9;
u32 /*unused*/:3;
  u32 horizontal_flip:1;
  u32 vertical_flip:1;
  u32 size:2;
  /* ATTR 2 */
  u32 base_tile_index:10;
  u32 priority:2;
  u32 palblock_index:4;
  /* AFFINE ATTR  */
s32 /*unused*/:16;

} ALIGN_WORD object_attribute_t;

typedef struct object_affine_attribute_tag {

  /* ATTR 0 */
  u32 Y:8;
  u32 mode:2;
  u32 gfx_mode:2;
  u32 enable_mosaic:1;
  u32 palette_bpp:1;
  u32 shape:2;
  /* ATTR 1 */
  u32 X:9;
  u32 affine_index:5;
  u32 size:2;
  /* ATTR 2 */
  u32 base_tile_index:10;
  u32 priority:2;
  u32 palblock_index:4;
  /* AFFINE ATTR  */
s32 /*unused*/:16;

} ALIGN_WORD object_affine_attribute_t;

typedef struct object_affine_tag {

  /* ATTR 0 */
u32 /*unused*/:32;
u32 /*unused*/:16;
  s32 attr0:16;
  /* ATTR 1 */
u32 /*unused*/:32;
u32 /*unused*/:16;
  s32 attr1:16;
  /* ATTR 2 */
u32 /*unused*/:32;
u32 /*unused*/:16;
  s32 attr2:16;
  /* ATTR 3 */
u32 /*unused*/:32;
u32 /*unused*/:16;
  s32 attr3:16;


} ALIGN_WORD object_affine_t;

#define OBJECT_MAX           (MEM_OAM_SIZE / sizeof(object_t))
#define OBJECT_ATTRIBUTE_MAX (MEM_OAM_SIZE / sizeof(object_attribute_t))
#define OBJECT_AFFINE_MAX    (MEM_OAM_SIZE / sizeof(object_affine_t))

typedef object_t                  object_block_t[OBJECT_MAX];
typedef object_attribute_t        object_attrblock_t[OBJECT_MAX];
typedef object_affine_attribute_t object_affattrblock_t[OBJECT_ATTRIBUTE_MAX];
typedef object_affine_t           object_affblock_t[OBJECT_AFFINE_MAX];

#define MEM_OBJECT                   ((object_block_t *)        MEM_OAM)
#define MEM_OBJECT_ATTRIBUTE         ((object_attrblock_t *)    MEM_OAM)
#define MEM_OBJECT_AFFINE_ATTRIBUTE  ((object_affattrblock_t *) MEM_OAM)
#define MEM_OBJECT_AFFINE            ((object_affblock_t *)     MEM_OAM)

extern object_attribute_t const OBJECT_ATTRIBUTE_INIT;

INLINE void object_attribute_setX(object_attribute_t *obj_attr,
				  u32 x) {

  obj_attr->X = x & 0x01FF;

}

INLINE void object_attribute_setY(object_attribute_t *obj_attr,
				  u32 y) {

  obj_attr->Y = y & 0x00FF;

}

INLINE void object_attribute_set_pos(object_attribute_t *obj_attr,
				     u32 x,
				     u32 y) {

  obj_attr->X = x & 0x01FF;
  obj_attr->Y = y & 0x00FF;

}

void object_init(object_block_t *buffer,
		 u32 buffer_size);
void object_copy(object_block_t *dst,
		 object_block_t *src,
		 u32 src_size);

#endif
