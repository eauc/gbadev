#include <display.h>

void display_control_init(void) {

  REG_DISPLAY_CONTROL.mode = 0;
  REG_DISPLAY_CONTROL.render_page = 0;
  REG_DISPLAY_CONTROL.allow_OAM_in_hblank = FALSE;
  REG_DISPLAY_CONTROL.object_mapping_mode = MAPPING_1D;
  REG_DISPLAY_CONTROL.force_blank = FALSE;
  REG_DISPLAY_CONTROL.render_background0 = FALSE;
  REG_DISPLAY_CONTROL.render_background1 = FALSE;
  REG_DISPLAY_CONTROL.render_background2 = FALSE;
  REG_DISPLAY_CONTROL.render_background3 = FALSE;
  REG_DISPLAY_CONTROL.render_object = FALSE;
  REG_DISPLAY_CONTROL.render_window0 = FALSE;
  REG_DISPLAY_CONTROL.render_window1 = FALSE;
  REG_DISPLAY_CONTROL.render_object_window = FALSE;

}
