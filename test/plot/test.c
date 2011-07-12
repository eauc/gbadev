#include "screen.h"
#include "display.h"
#include "color.h"
#include "m3.h"

int main(void) {

  u32 count = 1;

  busy_wait_vsync();

  display_control_init();


  REG_DISPLAY_CONTROL.mode = 3;
  REG_DISPLAY_CONTROL.render_background2 = TRUE;

  for(count = 0;
      count < 0x20;
      count++) {

    m3_plot(20+count,120,RGB15(count,0,0));
    m3_plot(20+count,130,RGB15(0,count,0));
    m3_plot(20+count,140,RGB15(0,0,count));

  }
  m3_circle(50,40,25,RGB15_GREEN);
  m3_filled_circle(40,35,10,RGB15_GREEN);
  m3_rect(10,230,50,150,RGB15_YELLOW);
  m3_filled_rect(15,225,45,155,RGB15_YELLOW);

  for(count = 0;
      count < 10;
      count++) {

    m3_line(120,80+7*count,127+7*count,150,RGB15_RED);
    m3_line(120+7*count,150,190,143-7*count,RGB15_CIAN);
    m3_line(190,150-7*count,183-7*count,80,RGB15_PURPLE);
    m3_line(190-7*count,80,120,87+7*count,RGB15_BLUE);

  }

  while(1) {

    busy_wait_vsync();

  }

}
