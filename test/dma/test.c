#include <screen.h>
#include <display.h>
#include <input.h>
#include <background.h>
#include <color.h>
#include <dma.h>

#define CBB_0 0
#define SBB_0 28

#define CROSS_TX 15
#define CROSS_TY 10

background_offset_t bg0_offset = {0,0};

screen_entry_t *bg0_map = 0;

u32 se_index(u32 tx,
	     u32 ty,
	     u32 pitch) {

  u32 sbb = (tx >> 5) + (ty >> 5) * (pitch >> 5);
  return sbb * 1024 + (tx & 31) + (ty & 31) * 32;

}

void init_map() {

  s32 ii = 0;
  screen_entry_t *sce = bg0_map;
  tile_t tiles[2] ALIGN_WORD = 
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

  /* MEM_TILE[CBB_0][0] = tiles[0]; */
  /* MEM_TILE[CBB_0][1] = tiles[1]; */

  dma_cpy(MEM_TILE[CBB_0],
  	  tiles,
  	  2 * sizeof(tile_t),
  	  3,DMA_32);

  MEM_PALBLOCK_4BPP[0][1] = RGB15_RED;
  MEM_PALBLOCK_4BPP[1][1] = RGB15_BLUE;
  MEM_PALBLOCK_4BPP[2][1] = RGB15_GREEN;
  MEM_PALBLOCK_4BPP[3][1] = RGB15(16,16,16);

  for(ii = 0 ;
      ii < 4 ;
      ii ++) {

    screen_entry_t temp = {
      { 0 },
    };
    temp.palblock_index = ii;
    dma_set16(&(sce[1024 * ii]),temp.raw_data,1024*sizeof(temp.raw_data),3);

  }

}

int main(void) {

  unsigned int i;
  u32 tx = 0;
  u32 ty = 0;
  u32 se_curr = 0;
  u32 se_prev = CROSS_TY * 32 + CROSS_TX;
  u16 offset[SCREEN_HEIGHT];

  for(i=0 ; i<SCREEN_HEIGHT ; i++) {

    offset[i] = i+1 + 0x1400;

  }

  bg0_map = MEM_MAP[SBB_0];

  busy_wait_vsync();

  init_map();
  display_control_init();
  REG_DISPLAY_CONTROL.render_background0 = TRUE;
  REG_DISPLAY_CONTROL.render_object = TRUE;
  REG_WINDOW0_LR_BOUND.low = 20;
  REG_WINDOW0_LR_BOUND.high = 220;
  REG_WINDOW0_TB_BOUND.low = 20;
  REG_WINDOW0_TB_BOUND.high = 140;
  REG_WINDOW_I_CONTROL.win0_background0 = TRUE;
  REG_DISPLAY_CONTROL.render_window0 = TRUE;
  bg0_map[se_prev].tile_index++;

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
    
    dma_hblank(&(REG_WINDOW0_LR_BOUND),
	       offset,
	       2,
	       3, DMA_16, DMA_ADJ_INCREMENT);
  
  }
  return 0;

}
