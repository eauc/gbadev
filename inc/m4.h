#ifndef M4_H_
#define M4_H_

#include <types.h>
#include <mem.h>
#include <display.h>
#include <screen.h>
#include <color.h>

#define M4_SCREEN_WIDTH   SCREEN_WIDTH

#define M4_MEM_VIDEO      ((u16 *) MEM_VIDEO)
#define M4_MEM_PAGE_FLIP  0xA000
#define m4_vid_page       ((u16 *) MEM_VIDEO)

INLINE void m4_page_flip() {

  m4_vid_page = (u16 *)(((u32)m4_vid_page) ^ M4_MEM_PAGE_FLIP);
  REG_DISPLAY_CONTROL.render_page ^= 0x01;

}

INLINE void m4_plot(screen_coord_t x,
		    screen_coord_t y,
		    palette_index_t index) {

  u16 *twin_pixel = m4_vid_page + (x + y * M4_SCREEN_WIDTH) / 2;
  if(0x01 & x) {

    *twin_pixel = ((*twin_pixel) & 0x00FF) | (index << 8);

  }
  else {

    *twin_pixel = ((*twin_pixel) & 0xFF00) | index;

  }

}

#endif
