#include "screen.h"
#include "display.h"
#include "color.h"
#include "m3.h"
#include "input.h"

int main(void) {

  busy_wait_vsync();

  display_control_init();

  while(1) {

    busy_wait_vsync();

  }

}
