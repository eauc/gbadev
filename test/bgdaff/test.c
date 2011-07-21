#include <display.h>
#include <input.h>
#include <background.h>
#include <color.h>
#include <affine.h>
#include <interrupt.h>
#include <bios.h>

void init_map() {

  s32 jj = 0;

  const tile_8bpp_t tiles[4] = 
    {
      {{0x01010101,0x01010101,
	0x01010101,0x00010101,
	0x01010101,0x00010101,
	0x01010101,0x00010101,
	0x01010101,0x00010101,
	0x01010101,0x00010101,
	0x01010101,0x00010101,
	0x00000001,0x00000000,}},
      {{0x02020202,0x02020202,
	0x02020202,0x00020202,
	0x02020202,0x00020202,
	0x02020202,0x00020202,
	0x02020202,0x00020202,
	0x02020202,0x00020202,
	0x02020202,0x00020202,
	0x00000002,0x00000000,}},
      {{0x03030303,0x03030303,
	0x03030303,0x00030303,
	0x03030303,0x00030303,
	0x03030303,0x00030303,
	0x03030303,0x00030303,
	0x03030303,0x00030303,
	0x03030303,0x00030303,
	0x00000003,0x00000000,}},
      {{0x04040404,0x04040404,
	0x04040404,0x00040404,
	0x04040404,0x00040404,
	0x04040404,0x00040404,
	0x04040404,0x00040404,
	0x04040404,0x00040404,
	0x04040404,0x00040404,
	0x00000004,0x00000000,}},
    };

  REG_BACKGROUND2_CONTROL.charblock_index = 0;
  REG_BACKGROUND2_CONTROL.screenblock_index = 8;
  REG_BACKGROUND2_CONTROL.size = AFFINE_SIZE_64_64;
  REG_BACKGROUND2_OFFSET.Y = 0;
  REG_BACKGROUND2_OFFSET.Y = 0;
  REG_BACKGROUND2_AFFINE.attr0 = 256;
  REG_BACKGROUND2_AFFINE.attr1 = 0;
  REG_BACKGROUND2_AFFINE.attr2 = 0;
  REG_BACKGROUND2_AFFINE.attr3 = 256;
  REG_BACKGROUND2_AFFINE.dx = 0;
  REG_BACKGROUND2_AFFINE.dy = 0;

  MEM_TILE_8BPP[0][0] = tiles[0];
  MEM_TILE_8BPP[0][1] = tiles[1];
  MEM_TILE_8BPP[0][2] = tiles[2];
  MEM_TILE_8BPP[0][3] = tiles[3];

  MEM_PALBLOCK[0][1] = RGB15_RED;
  MEM_PALBLOCK[0][2] = RGB15_BLUE;
  MEM_PALBLOCK[0][3] = RGB15_GREEN;
  MEM_PALBLOCK[0][4] = RGB15(16,16,16);

  u32 *mem_map = (u32 *)(MEM_MAP[8]);
  for(jj = 0 ;
      jj < 256 ; /* 64*16/4 */
      jj++) {

    mem_map[jj] = 0x00000000;
    
  }
  for(jj = 0 ;
      jj < 256 ; /* 64*16/4 */
      jj++) {

    mem_map[256+jj] = 0x01010101;
    
  }
  for(jj = 0 ;
      jj < 256 ; /* 64*16/4 */
      jj++) {

    mem_map[512+jj] = 0x02020202;
    
  }
  for(jj = 0 ;
      jj < 256 ; /* 64*16/4 */
      jj++) {

    mem_map[768+jj] = 0x03030303;
    
  }

}

int main(void) {

  affine_t current_affine = identity;

  interrupt_init_vector();
  interrupt_add(INTERRUPT_VBLANK, NULL);
  REG_INTERRUPT_MASTER_ENABLE = TRUE;

  init_map();
  display_control_init();
  REG_DISPLAY_CONTROL.mode = 1;
  REG_DISPLAY_CONTROL.render_background2 = TRUE;
  REG_DISPLAY_CONTROL.render_object = TRUE;
  REG_DISPLAY_STATUS.enable_vblank_irq = TRUE;

  while(1) {

    bios_wait_vsync();

    input_poll();

    if(input_released_status.start) {

      current_affine = identity;

    }
    if(KEY_DOWN == input_current_status.A) {

      if(KEY_DOWN == input_current_status.right) {

	current_affine.scale.x += 1;

      }
      else if(KEY_DOWN == input_current_status.left) {

	current_affine.scale.x -= 1;

      }
      if(KEY_DOWN == input_current_status.up) {

	current_affine.scale.y -= 1;

      }
      else if(KEY_DOWN == input_current_status.down) {

	current_affine.scale.y += 1;

      }

    }
    else if(KEY_DOWN == input_current_status.select) {

      if(KEY_DOWN == input_current_status.right) {

	current_affine.screen_anchor.x += 1<<8;

      }
      else if(KEY_DOWN == input_current_status.left) {

	current_affine.screen_anchor.x -= 1<<8;

      }
      if(KEY_DOWN == input_current_status.up) {

	current_affine.screen_anchor.y -= 1<<8;

      }
      else if(KEY_DOWN == input_current_status.down) {

	current_affine.screen_anchor.y += 1<<8;

      }

    }
    else {

      if(KEY_DOWN == input_current_status.right) {

	current_affine.map_anchor.x += 1<<8;

      }
      else if(KEY_DOWN == input_current_status.left) {

	current_affine.map_anchor.x -= 1<<8;

      }
      if(KEY_DOWN == input_current_status.up) {

	current_affine.map_anchor.y -= 1<<8;

      }
      else if(KEY_DOWN == input_current_status.down) {

	current_affine.map_anchor.y += 1<<8;

      }

    }
    if(KEY_DOWN == input_current_status.L) {

      current_affine.rotation += 1<<6;

    }
    else if(KEY_DOWN == input_current_status.R) {

      current_affine.rotation -= 1<<6;

    }
    affine_to_background(_reg_background2_affine,
			 &current_affine,
			 1);
      
    /* tx = ((bg0_offset.X >> 3) + CROSS_TX) & 0x3F; */
    /* ty = ((bg0_offset.Y >> 3) + CROSS_TY) & 0x3F; */

    /* se_curr = se_index(tx,ty,64); */
    /* if(se_curr != se_prev) { */

    /*   bg0_map[se_prev].tile_index--; */
    /*   bg0_map[se_curr].tile_index++; */
    /*   se_prev = se_curr; */

    /* } */
    /* REG_BACKGROUND0_OFFSET = bg0_offset; */

  }
  return 0;

}
