#include <types.h>
#include <color.h>
#include <display.h>
#include <screen.h>
#include <interrupt.h>

IWRAM_CODE void hblank_handler(void) {

  u16 i = 0;

  /* MEM_PALBLOCK_4BPP[0][1] = RGB15_GREEN; */
  if(SCREEN_HEIGHT <= REG_DISPLAY_VCOUNT) {

    i = 0;

  }
  else {

    i = REG_DISPLAY_VCOUNT / 5;

  }
  MEM_PALBLOCK_4BPP[0][1] = RGB15(31-i,0,i);

}

IWRAM_CODE void vcount_handler(void) {

  MEM_PALBLOCK_4BPP[0][1] = RGB15_GREEN;
  while(REG_DISPLAY_VCOUNT < 120);

}

IWRAM_CODE void vcount_handler_reentrant(void) {

  MEM_PALBLOCK_4BPP[0][1] = RGB15_GREEN;
  REG_INTERRUPT_ENABLE.raw_data = (1 << INTERRUPT_HBLANK);
  REG_INTERRUPT_MASTER_ENABLE = TRUE;
  while(REG_DISPLAY_VCOUNT < 120);

}
