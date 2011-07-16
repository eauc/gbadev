#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <mem.h>
#include <types.h>

/*
  Main Display Registers
*/

typedef enum display_control_object_mapping {

  MAPPING_2D = 0,
  MAPPING_1D = 1

} display_control_object_mapping_t; 

typedef struct display_control_tag {

  vu16 mode:3;
  vu16 is_gbc:1;
  vu16 render_page:1;
  vu16 allow_OAM_in_hblank:1;
  vu16 object_mapping_mode:1;
  vu16 force_blank:1;
  vu16 render_background0:1;
  vu16 render_background1:1;
  vu16 render_background2:1;
  vu16 render_background3:1;
  vu16 render_object:1;
  vu16 render_window0:1;
  vu16 render_window1:1;
  vu16 render_object_window:1;

} ALIGN_HALF_WORD display_control_t;

typedef struct display_status_tag {

  vu16 in_vblank:1;
  vu16 in_hblank:1;
  vu16 in_vtrigger:1;
  vu16 enable_vblank_irq:1;
  vu16 enable_hblank_irq:1;
  vu16 enable_vcount_irq:1;
vu16 /*unused*/:2;
  vu16 vtrigger:8;

} ALIGN_HALF_WORD display_status_t;

typedef struct display_vcount_tag {

  vu16 value:8;

} ALIGN_HALF_WORD display_vcount_t;

#define _reg_display_control  ((display_control_t *)(MEM_IO + 0x0000))
#define _reg_display_status   ((display_status_t *) (MEM_IO + 0x0004))
#define _reg_display_vcount   ((display_vcount_t *) (MEM_IO + 0x0006))

#define REG_DISPLAY_CONTROL  (*_reg_display_control)
#define REG_DISPLAY_STATUS   (*_reg_display_status)
#define REG_DISPLAY_VCOUNT   (_reg_display_vcount->value)

void display_control_init(void);

INLINE void busy_wait_vsync() {

  while(REG_DISPLAY_VCOUNT >= 160);
  while(REG_DISPLAY_VCOUNT < 160);

}

/*
  Windows Registers
*/

typedef struct window_control_tag {
  
  vu16 win0_background0:1;
  vu16 win0_background1:1;
  vu16 win0_background2:1;
  vu16 win0_background3:1;
  vu16 win0_object:1;
  vu16 win0_blend:1;
vu16 /* unused */:2;
  vu16 win1_background0:1;
  vu16 win1_background1:1;
  vu16 win1_background2:1;
  vu16 win1_background3:1;
  vu16 win1_object:1;
  vu16 win1_blend:1;
vu16 /* unused */:2;

} ALIGN_HALF_WORD window_control_t;

typedef struct window_bound_tag {
  
  vu16 high:8;
  vu16 low:8;

} ALIGN_HALF_WORD window_bound_t;

#define _reg_window0_lr_bound ((window_bound_t *)   (MEM_IO + 0x0040))
#define _reg_window0_tb_bound ((window_bound_t *)   (MEM_IO + 0x0044))
#define _reg_window1_lr_bound ((window_bound_t *)   (MEM_IO + 0x0042))
#define _reg_window1_tb_bound ((window_bound_t *)   (MEM_IO + 0x0046))
#define _reg_window_i_control ((window_control_t *) (MEM_IO + 0x0048))
#define _reg_window_o_control ((window_control_t *) (MEM_IO + 0x004A))

#define REG_WINDOW0_LR_BOUND (*_reg_window0_lr_bound)
#define REG_WINDOW0_TB_BOUND (*_reg_window0_tb_bound)
#define REG_WINDOW1_LR_BOUND (*_reg_window1_lr_bound)
#define REG_WINDOW1_TB_BOUND (*_reg_window1_tb_bound)
#define REG_WINDOW_I_CONTROL (*_reg_window_i_control)
#define REG_WINDOW_O_CONTROL (*_reg_window_o_control)

/*
  Mosaic Registers
*/

typedef struct mosaic_control_tag {

  vu16 background_x:4;
  vu16 background_y:4;
  vu16 object_x:4;
  vu16 object_y:4;

} ALIGN_HALF_WORD mosaic_control_t;

#define _reg_mosaic_control   ((mosaic_control_t *) (MEM_IO + 0x004C))

#define REG_MOSAIC_CONTROL   (*_reg_mosaic_control)

/*
  Blending Registers
*/

typedef enum blend_control_mode {

  BLEND_OFF = 0x00,
  BLEND_STANDARD = 0x01,
  BLEND_WHITE = 0x02,
  BLEND_BLACK = 0x03,

} blend_control_mode_t; 

typedef struct blend_control_tag {

  vu16 A_background0:1;
  vu16 A_background1:1;
  vu16 A_background2:1;
  vu16 A_background3:1;
  vu16 A_object:1;
  vu16 A_backdrop:1;
  vu16 mode:2;
  vu16 B_background0:1;
  vu16 B_background1:1;
  vu16 B_background2:1;
  vu16 B_background3:1;
  vu16 B_object:1;
  vu16 B_backdrop:1;
vu16 /* unused */ :2;

} ALIGN_HALF_WORD blend_control_t;

typedef struct blend_alpha_tag {

  vu16 A_blend:5;
vu16 /* unused */ :3;
  vu16 B_blend:5;
vu16 /* unused */ :3;

} ALIGN_HALF_WORD blend_alpha_t;

typedef struct blend_fade_tag {

  vu16 fade:5;
vu16 /* unused */ :11;

} ALIGN_HALF_WORD blend_fade_t;

#define _reg_blend_control    ((blend_control_t *)  (MEM_IO + 0x0050))
#define _reg_blend_alpha      ((blend_alpha_t *)    (MEM_IO + 0x0052))
#define _reg_blend_fade       ((blend_fade_t *)     (MEM_IO + 0x0054))

#define REG_BLEND_CONTROL    (*_reg_blend_control)
#define REG_BLEND_ALPHA      (*_reg_blend_alpha)
#define REG_BLEND_FADE       (*_reg_blend_fade)

#endif
