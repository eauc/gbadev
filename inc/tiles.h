#ifndef TILES_H_
#define TILES_H_

#include <mem.h>
#include <types.h>

typedef struct tile_4bpp_tag {

  u32 data[8];

} ALIGN_WORD tile_4bpp_t;

typedef struct tile_8bpp_tag {

  u32 data[16];

} ALIGN_WORD tile_8bpp_t;

typedef tile_4bpp_t tile_t;

#define CHARBLOCK_MAX            6
#define CHARBLOCK_SIZE           (MEM_VIDEO_SIZE / CHARBLOCK_MAX)
#define CHARBLOCK_TILE_8BPP_MAX  (CHARBLOCK_SIZE / sizeof(tile_8bpp_t))
#define CHARBLOCK_TILE_4BPP_MAX  (CHARBLOCK_SIZE / sizeof(tile_4bpp_t))

typedef tile_4bpp_t charblock_4bpp_t[CHARBLOCK_TILE_4BPP_MAX];
typedef tile_8bpp_t charblock_8bpp_t[CHARBLOCK_TILE_8BPP_MAX];
typedef charblock_4bpp_t  charblock_t;

#define MEM_TILE_4BPP  ((charblock_4bpp_t *) MEM_VIDEO)
#define MEM_TILE_8BPP  ((charblock_8bpp_t *) MEM_VIDEO)
#define MEM_TILE       ((charblock_t *)      MEM_VIDEO)

#define CHARBLOCK_BACKGROUND1 0
#define CHARBLOCK_BACKGROUND2 1
#define CHARBLOCK_BACKGROUND3 2
#define CHARBLOCK_BACKGROUND4 3

#define CHARBLOCK_OBJECT      4
#define CHARBLOCK_OBJECT_LOW  4
#define CHARBLOCK_OBJECT_HIGH 5

#endif
