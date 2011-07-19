#include <types.h>
#include <color.h>
#include <display.h>
#include <screen.h>

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
