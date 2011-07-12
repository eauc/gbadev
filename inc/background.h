#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include <mem.h>
#include <types.h>
#include <tiles.h>

enum {

  PALETTE_4BPP = 0,
  PALETTE_8BPP = 1

};

enum {

  REGULAR_SIZE_32_32 = 0x00,
  REGULAR_SIZE_64_32 = 0x01,
  REGULAR_SIZE_32_64 = 0x02,
  REGULAR_SIZE_64_64 = 0x03

};

enum {

  AFFINE_SIZE_16_16 = 0x00,
  AFFINE_SIZE_32_32 = 0x01,
  AFFINE_SIZE_64_64 = 0x02,
  AFFINE_SIZE_128_128 = 0x03

};

typedef struct background_control_tag {

  u32 priority:2;
  u32 charblock_index:2;
u32 /*unused*/:2;
  u32 enable_mosaic:1;
  u32 palette_bpp:1;
  u32 screenblock_index:5;
  u32 enable_wrapping:1;
  u32 size:2;

} ALIGN_HALF_WORD background_control_t;

typedef struct background_control_affine_tag {

  s16 pa;
  s16 pb;
  s16 pc;
  s16 pd;
  u32 dx;
  u32 dy;

} ALIGN_WORD background_affine_control_t;

typedef struct background_offset_tag {

  u16 X;
  u16 Y;

} ALIGN_WORD background_offset_t;

#define _reg_background0_affine_control  ((background_affine_control_t *)(MEM_IO + 0x0008))

#define _reg_background0_control         ((background_control_t *)(MEM_IO + 0x0008))
#define _reg_background1_control         ((background_control_t *)(MEM_IO + 0x000A))
#define _reg_background2_control         ((background_control_t *)(MEM_IO + 0x000C))
#define _reg_background3_control         ((background_control_t *)(MEM_IO + 0x000E))

#define _reg_background0_offset          ((background_offset_t *)(MEM_IO + 0x0010))
#define _reg_background1_offset          ((background_offset_t *)(MEM_IO + 0x0014))
#define _reg_background2_offset          ((background_offset_t *)(MEM_IO + 0x0018))
#define _reg_background3_offset          ((background_offset_t *)(MEM_IO + 0x001C))

#define REG_BACKGROUND0_AFFINE_CONTROL (*_reg_background0_affine_control)

#define REG_BACKGROUND0_CONTROL        (*_reg_background0_control)
#define REG_BACKGROUND1_CONTROL        (*_reg_background1_control)
#define REG_BACKGROUND2_CONTROL        (*_reg_background2_control)
#define REG_BACKGROUND3_CONTROL        (*_reg_background3_control)

#define REG_BACKGROUND0_OFFSET         (*_reg_background0_offset)
#define REG_BACKGROUND1_OFFSET         (*_reg_background1_offset)
#define REG_BACKGROUND2_OFFSET         (*_reg_background2_offset)
#define REG_BACKGROUND3_OFFSET         (*_reg_background3_offset)

typedef struct screen_entry_tag {

  union {

    u16 raw_data;
    struct {
      
      u16 tile_index:10;
      u16 vertical_flip:1;
      u16 horizontal_flip:1;
      u16 palblock_index:4;

    };

  };

} ALIGN_HALF_WORD screen_entry_t;

#define SCREENBLOCK_CHARBLOCK_USED  4
#define SCREENBLOCK_MEM_SIZE        (MEM_VIDEO_SIZE * SCREENBLOCK_CHARBLOCK_USED / CHARBLOCK_MAX)
#define SCREENBLOCK_MAX             32
#define SCREENBLOCK_SIZE            (SCREENBLOCK_MEM_SIZE / SCREENBLOCK_MAX)
#define SCREENBLOCK_ENTRY_MAX       (SCREENBLOCK_SIZE / sizeof(u16))

typedef screen_entry_t screenblock_t[SCREENBLOCK_ENTRY_MAX];

#define MEM_MAP  ((screenblock_t *)MEM_VIDEO)

#endif
