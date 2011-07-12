#ifndef COLOR_H_
#define COLOR_H_

#include <mem.h>
#include <types.h>

/*
  COLORS
*/

typedef u16 color_t;

#define RGB15_BLACK   ((color_t)0x0000)
#define RGB15_RED     ((color_t)0x001F)
#define RGB15_YELLOW  ((color_t)0x03FF)
#define RGB15_GREEN   ((color_t)0x03E0)
#define RGB15_CIAN    ((color_t)0x7FE0)
#define RGB15_BLUE    ((color_t)0x7C00)
#define RGB15_PURPLE  ((color_t)0x7C1F)
#define RGB15_WHITE   ((color_t)0xFFFF)

INLINE color_t RGB15(u32 red,
		     u32 green,
		     u32 blue) {

  return red | (green << 5) | (blue << 10);

}

/*
  PALETTES
*/

typedef color_t palette_8bpp_t[256];
typedef color_t palette_4bpp_t[16];
typedef palette_8bpp_t palette_t;

#define PALBLOCK_8BPP_MAX (MEM_PALETTE_SIZE/sizeof(palette_8bpp_t))
#define PALBLOCK_4BPP_MAX (MEM_PALETTE_SIZE/sizeof(palette_4bpp_t))

typedef palette_8bpp_t   palblock_8bpp_t[PALBLOCK_8BPP_MAX];
typedef palette_4bpp_t   palblock_4bpp_t[PALBLOCK_4BPP_MAX];
typedef palblock_8bpp_t  palblock_t; 

typedef u8 palette_8bpp_index_t;
typedef u8 palette_4bpp_index_t;
typedef palette_8bpp_index_t palette_index_t;

#define MEM_PALBLOCK_8BPP  ((palette_8bpp_t *) MEM_PALETTE)
#define MEM_PALBLOCK_4BPP  ((palette_4bpp_t *) MEM_PALETTE)
#define MEM_PALBLOCK       ((palette_t *)      MEM_PALETTE)

#define PALBLOCK_8BPP_BACKGROUND 0
#define PALBLOCK_4BPP_BACKGROUND 0
#define PALBLOCK_BACKGROUND      0

#define PALBLOCK_8BPP_OBJECT     1
#define PALBLOCK_4BPP_OBJECT     16
#define PALBLOCK_OBJECT          1

#endif
