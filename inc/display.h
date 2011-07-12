#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <mem.h>
#include <types.h>

/*
  REGISTERS
*/

typedef enum display_control_object_mapping {

  MAPPING_2D = 0,
  MAPPING_1D = 1

} display_control_object_mapping_t; 

typedef struct display_control_tag {

  vu32 mode:3;
  vu32 is_gbc:1;
  vu32 render_page:1;
  vu32 allow_OAM_in_hblank:1;
  vu32 object_mapping_mode:1;
  vu32 force_blank:1;
  vu32 render_background0:1;
  vu32 render_background1:1;
  vu32 render_background2:1;
  vu32 render_background3:1;
  vu32 render_object:1;
  vu32 render_window0:1;
  vu32 render_window1:1;
  vu32 render_object_window:1;

} ALIGN_WORD display_control_t;

typedef struct display_status_tag {

  vu32 in_vblank:1;
  vu32 in_hblank:1;
  vu32 in_vtrigger:1;
  vu32 enable_vblank_irq:1;
  vu32 enable_hblank_irq:1;
  vu32 enable_vcount_irq:1;
vu32 /*unused*/:2;
  vu32 vtrigger:8;

} ALIGN_WORD display_status_t;

typedef struct display_vcount_tag {

  vu16 value:8;

} ALIGN_HALF_WORD display_vcount_t;

#define _reg_display_control ((display_control_t *)(MEM_IO + 0x0000))
#define _reg_display_status  ((display_status_t *) (MEM_IO + 0x0004))
#define _reg_display_vcount  ((display_vcount_t *) (MEM_IO + 0x0006))

#define REG_DISPLAY_CONTROL (*_reg_display_control)
#define REG_DISPLAY_STATUS  (*_reg_display_status)
#define REG_DISPLAY_VCOUNT  ((*_reg_display_vcount).value)

void display_control_init(void);

INLINE void busy_wait_vsync() {

  while(REG_DISPLAY_VCOUNT >= 160);
  while(REG_DISPLAY_VCOUNT < 160);

}

#endif
