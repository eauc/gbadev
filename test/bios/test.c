#include <screen.h>
#include <display.h>
#include <color.h>
#include <m3.h>
#include <bios.h>
#include <input.h>
#include <interrupt.h>

void div_plot(void) {

  screen_coord_t x = 0;
  screen_coord_t y = 0;

  for(x = 0 ; x < SCREEN_WIDTH ; x++) {

    y = bios_div(0x0A00, x + 1);
    if(y < SCREEN_HEIGHT) {

      m3_plot(x, SCREEN_HEIGHT - y, RGB15_RED);

    }

  }

}

void sqrt_plot(void) {

  screen_coord_t x = 0;
  screen_coord_t y = 0;

  for(x = 0 ; x < SCREEN_WIDTH ; x++) {

    y = bios_sqrt(x << 6);
    if(y < SCREEN_HEIGHT) {

      m3_plot(x, SCREEN_HEIGHT - y, RGB15_GREEN);

    }

  }

}

void atan2_plot(void) {

  screen_coord_t x = 0;
  s16 y = 0;
  screen_coord_t half_x = SCREEN_WIDTH >> 1;

  for(x = 0 ; x < SCREEN_WIDTH ; x++) {

    y = bios_atan2((x-half_x)<<8,0x4000);
    y = y >> 8;
    if(ABS(y) < SCREEN_HEIGHT) {

      m3_plot(x, SCREEN_HEIGHT - y, RGB15_BLUE);

    }

  }

}

int main(void) {

  interrupt_init_vector();
  interrupt_add(INTERRUPT_VBLANK,
		NULL);

  display_control_init();
  REG_DISPLAY_CONTROL.mode = 3;
  REG_DISPLAY_CONTROL.render_background2 = TRUE;
  REG_DISPLAY_STATUS.enable_vblank_irq = TRUE;

  div_plot();
  sqrt_plot();
  atan2_plot();

  while(1) {

    bios_wait_vsync();

    input_poll();

    if(KEY_DOWN == input_current_status.start) {

      m3_plot(120, 20, RGB15_WHITE);

    }
    else {

      m3_plot(120, 20, RGB15_BLUE);

    }

  }

}
