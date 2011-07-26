#include <screen.h>
#include <display.h>
#include <background.h>
#include <color.h>
#include <m3.h>
#include <m4.h>
#include <input.h>

extern u32 panty_24bpp_data_size;
extern u32 panty_24bpp_data_width;
extern u32 panty_24bpp_data_height;
extern u16 panty_24bpp_data[];

extern u32 panty_8bpp_palette_size;
extern u16 panty_8bpp_palette[];
extern u32 panty_8bpp_data_size;
extern u32 panty_8bpp_data_width;
extern u32 panty_8bpp_data_height;
extern u16 panty_8bpp_data[];

extern u32 panty_8bpp_tiled_palette_size;
extern u16 panty_8bpp_tiled_palette[];
extern u32 panty_8bpp_tiled_tiles_size;
extern u32 panty_8bpp_tiled_tiles_width;
extern u32 panty_8bpp_tiled_tiles_height;
extern tile_8bpp_t panty_8bpp_tiled_tiles[];

extern u32 panty_4bpp_tiled_palette_size;
extern u16 panty_4bpp_tiled_palette[];
extern u32 panty_4bpp_tiled_tiles_size;
extern u32 panty_4bpp_tiled_tiles_width;
extern u32 panty_4bpp_tiled_tiles_height;
extern tile_4bpp_t panty_4bpp_tiled_tiles[];

int main(void) {

  u32 i, j;

  busy_wait_vsync();

  display_control_init();

  while(1) {

    busy_wait_vsync();

    input_poll();

    if(input_hit_status.A) {

      REG_DISPLAY_CONTROL.mode = 3;
      REG_DISPLAY_CONTROL.render_background2 = TRUE;

      for(i = 0 ; i < panty_24bpp_data_height ; i++) {

	for(j = 0 ; j < panty_24bpp_data_width ; j++) {

	  M3_MEM_VIDEO[i * SCREEN_WIDTH + j] = 
	    panty_24bpp_data[i * panty_24bpp_data_width + j];

	}

      }

    }
    else if(input_hit_status.B) {

      REG_DISPLAY_CONTROL.mode = 4;
      REG_DISPLAY_CONTROL.render_background2 = TRUE;
      REG_DISPLAY_CONTROL.render_page = 0;

      for(i = 0 ; i < panty_8bpp_palette_size ; i++) {

	MEM_PALBLOCK_8BPP[PALBLOCK_8BPP_BACKGROUND][i] =
	  panty_8bpp_palette[i];

      }

      for(i = 0 ; i < panty_8bpp_data_height ; i++) {

	for(j = 0 ; j < panty_8bpp_data_width ; j++) {

	  m4_vid_page[i * SCREEN_WIDTH / 2 + j] = 
	    panty_8bpp_data[i * panty_8bpp_data_width + j];

	}

      }

    }
    else if(input_hit_status.L) {

      REG_DISPLAY_CONTROL.mode = 1;
      REG_DISPLAY_CONTROL.render_background2 = TRUE;

      REG_BACKGROUND2_CONTROL.charblock_index = 0;
      REG_BACKGROUND2_CONTROL.screenblock_index = 16;
      REG_BACKGROUND2_CONTROL.size = AFFINE_SIZE_32_32;
      REG_BACKGROUND2_CONTROL.palette_bpp = PALETTE_8BPP;
      REG_BACKGROUND2_OFFSET.Y = 0;
      REG_BACKGROUND2_OFFSET.Y = 0;
      REG_BACKGROUND2_AFFINE.attr0 = 256;
      REG_BACKGROUND2_AFFINE.attr1 = 0;
      REG_BACKGROUND2_AFFINE.attr2 = 0;
      REG_BACKGROUND2_AFFINE.attr3 = 256;
      REG_BACKGROUND2_AFFINE.dx = 0;
      REG_BACKGROUND2_AFFINE.dy = 0;

      for(i = 0 ; i < panty_8bpp_tiled_palette_size ; i++) {

	MEM_PALBLOCK_8BPP[PALBLOCK_8BPP_BACKGROUND][i] =
	  panty_8bpp_tiled_palette[i];

      }

      for(i = 0 ; i < panty_8bpp_tiled_tiles_size ; i++) {

	MEM_TILE_8BPP[0][i] = panty_8bpp_tiled_tiles[i];

      }

      u32 *mem_map = (u32 *)(MEM_MAP[16]);
      for(i = 0 ; i < panty_8bpp_tiled_tiles_height ; i++) {

      	for(j = 0 ; j < panty_8bpp_tiled_tiles_width/4+1 ; j++) {

      	  u32 pixel = 0;
      	  u32 base_tile = i * panty_8bpp_tiled_tiles_width + j * 4;
      	  pixel += ((base_tile + 0) & 0xFF) << 0;
      	  pixel += ((base_tile + 1) & 0xFF) << 8;
      	  pixel += ((base_tile + 2) & 0xFF) << 16;
      	  pixel += ((base_tile + 3) & 0xFF) << 24;

      	  mem_map[i * 8 + j] = pixel;
    
      	}
	
      }

    }
#if 0
    else if(input_hit_status.R) {

      REG_DISPLAY_CONTROL.mode = 1;
      REG_DISPLAY_CONTROL.render_background2 = TRUE;

      REG_BACKGROUND2_CONTROL.charblock_index = 0;
      REG_BACKGROUND2_CONTROL.screenblock_index = 16;
      REG_BACKGROUND2_CONTROL.size = AFFINE_SIZE_32_32;
      REG_BACKGROUND2_CONTROL.palette_bpp = PALETTE_4BPP;
      REG_BACKGROUND2_OFFSET.Y = 0;
      REG_BACKGROUND2_OFFSET.Y = 0;
      REG_BACKGROUND2_AFFINE.attr0 = 256;
      REG_BACKGROUND2_AFFINE.attr1 = 0;
      REG_BACKGROUND2_AFFINE.attr2 = 0;
      REG_BACKGROUND2_AFFINE.attr3 = 256;
      REG_BACKGROUND2_AFFINE.dx = 0;
      REG_BACKGROUND2_AFFINE.dy = 0;

      for(i = 0 ; i < panty_4bpp_tiled_palette_size ; i++) {

	MEM_PALBLOCK_4BPP[PALBLOCK_4BPP_BACKGROUND][i] =
	  panty_4bpp_tiled_palette[i];

      }

      for(i = 0 ; i < panty_4bpp_tiled_tiles_size ; i++) {

	MEM_TILE_4BPP[0][i] = panty_4bpp_tiled_tiles[i];

      }

      u32 *mem_map = (u32 *)(MEM_MAP[16]);
      for(i = 0 ; i < panty_4bpp_tiled_tiles_height ; i++) {

      	for(j = 0 ; j < panty_4bpp_tiled_tiles_width/4+1 ; j++) {

      	  u32 pixel = 0;
      	  u32 base_tile = i * panty_4bpp_tiled_tiles_width + j * 4;
      	  pixel += ((base_tile + 0) & 0xFF) << 0;
      	  pixel += ((base_tile + 1) & 0xFF) << 8;
      	  pixel += ((base_tile + 2) & 0xFF) << 16;
      	  pixel += ((base_tile + 3) & 0xFF) << 24;

      	  mem_map[i * 8 + j] = pixel;
    
      	}
	
      }
      /* mem_map[0] = 0x03020100; */
      /* mem_map[1] = 0x04050607; */
      /* mem_map[2] = 0x08090a0b; */
      /* mem_map[3] = 0x0c0d0e0f; */

    }
#endif
  }

}
