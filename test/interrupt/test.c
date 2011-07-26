#include <display.h>
#include <input.h>
#include <background.h>
#include <color.h>
#include <timer.h>
#include <interrupt.h>

IWRAM_CODE void hblank_handler(void);
IWRAM_CODE void vcount_handler(void);
IWRAM_CODE void vcount_handler_reentrant(void);

#define CBB_0 0
#define SBB_0 28

#define CROSS_TX 15
#define CROSS_TY 10

background_offset_t bg0_offset = {0,0};

screen_entry_t *bg0_map = 0;

color_t colors[] = {
  RGB15_RED,
  RGB15_BLUE,
  RGB15_GREEN,
  RGB15_PURPLE,
};

u32 se_index(u32 tx,
	     u32 ty,
	     u32 pitch) {

  u32 sbb = (tx >> 5) + (ty >> 5) * (pitch >> 5);
  return sbb * 1024 + (tx & 31) + (ty & 31) * 32;

}

void init_map() {

  s32 ii = 0;
  s32 jj = 0;
  screen_entry_t *sce = bg0_map;

  const tile_t tiles[2] = 
    {
      {{0x11111111,0x11111101,0x11111101,0x11111101,
	0x11111101,0x11111101,0x11111101,0x00000001}},
      {{0x00000000,0x00100100,0x01100110,0x00011000,
	0x00011000,0x01100110,0x00100100,0x00000000}}
    };

  REG_BACKGROUND0_CONTROL.charblock_index = CBB_0;
  REG_BACKGROUND0_CONTROL.screenblock_index = SBB_0;
  REG_BACKGROUND0_CONTROL.size = REGULAR_SIZE_64_64;
  REG_BACKGROUND0_OFFSET.Y = 0;
  REG_BACKGROUND0_OFFSET.Y = 0;

  MEM_TILE[CBB_0][0] = tiles[0];
  MEM_TILE[CBB_0][1] = tiles[1];

  MEM_PALBLOCK_4BPP[0][1] = colors[0];
  MEM_PALBLOCK_4BPP[1][1] = colors[1];
  MEM_PALBLOCK_4BPP[2][1] = colors[2];
  MEM_PALBLOCK_4BPP[3][1] = colors[3];

  for(ii = 0 ;
      ii < 4 ;
      ii ++) {

    screen_entry_t temp = {{0}};
    temp.palblock_index = ii;
    for(jj = 0 ;
	jj < 1024 ; /* 32x32 */
	jj++) {

      sce->raw_data = temp.raw_data;
      sce++;

    }

  }

}

int main(void) {

  u32 tx = 0;
  u32 ty = 0;
  u32 se_curr = 0;
  u32 se_prev = CROSS_TY * 32 + CROSS_TX;

  bg0_map = MEM_MAP[SBB_0];

  busy_wait_vsync();

  init_map();
  display_control_init();
  REG_DISPLAY_CONTROL.render_background0 = TRUE;
  REG_DISPLAY_CONTROL.render_object = TRUE;
  REG_DISPLAY_STATUS.enable_hblank_irq = TRUE;
  REG_DISPLAY_STATUS.vtrigger = 80;
  REG_DISPLAY_STATUS.enable_vcount_irq = TRUE;

  bg0_map[se_prev].tile_index++;

  interrupt_init_vector();
  interrupt_add(INTERRUPT_HBLANK,
		(interrupt_handler_t)hblank_handler);
  interrupt_add(INTERRUPT_VCOUNT,
  		(interrupt_handler_t)vcount_handler);

  while(1) {

    busy_wait_vsync();

    input_poll();

    bg0_offset.X += input_tribool_horizontal();
    bg0_offset.Y += input_tribool_vertical();

    tx = ((bg0_offset.X >> 3) + CROSS_TX) & 0x3F;
    ty = ((bg0_offset.Y >> 3) + CROSS_TY) & 0x3F;

    se_curr = se_index(tx,ty,64);
    if(se_curr != se_prev) {

      bg0_map[se_prev].tile_index--;
      bg0_map[se_curr].tile_index++;
      se_prev = se_curr;

    }
    REG_BACKGROUND0_OFFSET = bg0_offset;

    if(input_hit_status.L) {

      interrupt_init_vector();
      interrupt_add(INTERRUPT_HBLANK,
		    (interrupt_handler_t)hblank_handler);
      interrupt_add(INTERRUPT_VCOUNT,
		    (interrupt_handler_t)vcount_handler);

    }
    else if(input_hit_status.R) {

      interrupt_init_vector_reentrant();
      interrupt_add(INTERRUPT_HBLANK,
		    (interrupt_handler_t)hblank_handler);
      interrupt_add(INTERRUPT_VCOUNT,
		    (interrupt_handler_t)vcount_handler);

    }
    if(input_hit_status.A) {

      interrupt_add(INTERRUPT_VCOUNT,
		    (interrupt_handler_t)vcount_handler);

    }
    else if(input_hit_status.B) {

      interrupt_add(INTERRUPT_VCOUNT,
		    (interrupt_handler_t)vcount_handler_reentrant);

    }
    
  }
  return 0;

}
