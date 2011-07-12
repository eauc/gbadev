#ifndef INPUT_H_
#define INPUT_H_

#include <mem.h>
#include <types.h>

typedef enum input_control_key_tag {

  KEY_DOWN = 0,
  KEY_UP = 1

} input_control_key_t;

typedef enum input_control_operator_tag {

  OPERATOR_OR = 0,
  OPERATOR_AND = 1

} input_control_operator_t;

typedef struct input_control_tag {

  vu32 enable_A_irq:1;
  vu32 enable_B_irq:1;
  vu32 enable_select_irq:1;
  vu32 enable_start_irq:1;
  vu32 enable_right_irq:1;
  vu32 enable_left_irq:1;
  vu32 enable_up_irq:1;
  vu32 enable_down_irq:1;
  vu32 enable_R_irq:1;
  vu32 enable_L_irq:1;
vu32 /*unused*/:4;
  vu32 master_enable:1;
  vu32 operator:1;

} input_control_t;

typedef struct input_status_tag {

  vu32 A:1;
  vu32 B:1;
  vu32 select:1;
  vu32 start:1;
  vu32 right:1;
  vu32 left:1;
  vu32 up:1;
  vu32 down:1;
  vu32 R:1;
  vu32 L:1;
vu32 /*unused*/:6;

} input_status_t;

#define _reg_input_control ((input_control_t *)(MEM_IO + 0x0132))
#define _reg_input_status  ((input_status_t *) (MEM_IO + 0x0130))

extern input_status_t input_current_status;
extern input_status_t input_previous_status;
extern input_status_t input_changed_status;
extern input_status_t input_hit_status;
extern input_status_t input_released_status;

#define REG_INPUT_CONTROL (*_reg_input_control)
#define REG_INPUT_STATUS  (*_reg_input_status)

INLINE void input_poll() {

  input_previous_status = input_current_status;
  input_current_status = REG_INPUT_STATUS;
  *((u32 *)&input_changed_status) = (*((u32 *)&input_current_status)) ^ (*((u32 *)&input_previous_status));
  *((u32 *)&input_hit_status) = (*((u32 *)&input_changed_status)) & (*((u32 *)&input_previous_status));
  *((u32 *)&input_released_status) = (*((u32 *)&input_changed_status)) & (*((u32 *)&input_current_status));

}

INLINE bool_t input_active() {

  return ((*((u32 *)&input_current_status)) ^ 0xFFFF) ? TRUE : FALSE;

}

INLINE s32 input_tribool_horizontal() {

  return input_current_status.left - input_current_status.right;

}

INLINE s32 input_tribool_vertical() {

  return input_current_status.up - input_current_status.down;

}

#endif
