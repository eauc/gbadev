#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <types.h>
#include <mem.h>

typedef void (*interrupt_handler_t)(void);

#define REG_INTERRUPT_HANDLER ( *((interrupt_handler_t *)(MEM_IC_WRAM + 0x7FFC)) )

typedef enum interrupt_flag_tag {

  INTERRUPT_VBLANK = 0,
  INTERRUPT_HBLANK,
  INTERRUPT_VCOUNT,
  INTERRUPT_TIMER0,
  INTERRUPT_TIMER1,
  INTERRUPT_TIMER2,
  INTERRUPT_TIMER3,
  INTERRUPT_COM,
  INTERRUPT_DMA0,
  INTERRUPT_DMA1,
  INTERRUPT_DMA2,
  INTERRUPT_DMA3,
  INTERRUPT_KEYBOARD,
  INTERRUPT_GAMEPACK,
  INTERRUPT_NB,

} interrupt_flag_t;

typedef union interrupt_control_tag {

  vu16 raw_data;
  struct {

    vu16 vblank:1;
    vu16 hblank:1;
    vu16 vcount:1;
    vu16 timer0:1;
    vu16 timer1:1;
    vu16 timer2:1;
    vu16 timer3:1;
    vu16 com:1;
    vu16 dma0:1;
    vu16 dma1:1;
    vu16 dma2:1;
    vu16 dma3:1;
    vu16 keyboard:1;
    vu16 gamepack:1;
  vu16 /*unused*/:2;

  };

} ALIGN_HALF_WORD interrupt_control_t;

#define _reg_interrupt_enable     ((interrupt_control_t *)(MEM_IO + 0x0200))
#define _reg_interrupt_flag       ((interrupt_control_t *)(MEM_IO + 0x0202))
#define _reg_interrupt_flag_bios  ((interrupt_control_t *)(MEM_IO + 0x7FF8))

#define REG_INTERRUPT_ENABLE        (*_reg_interrupt_enable)
#define REG_INTERRUPT_FLAG          (*_reg_interrupt_flag)
#define REG_INTERRUPT_FLAG_BIOS     (*_reg_interrupt_flag_bios)
#define REG_INTERRUPT_MASTER_ENABLE ( *((vu16 *)(MEM_IO + 0x0208)) )

extern interrupt_handler_t interrupt_vector[];

IWRAM_CODE void interrupt_default_handler(void);
IWRAM_CODE void interrupt_vector_handler(void);

INLINE interrupt_handler_t interrupt_remove(interrupt_flag_t number) {

  interrupt_handler_t current_handler = interrupt_vector[number];

  REG_INTERRUPT_MASTER_ENABLE = FALSE;
  interrupt_vector[number] = NULL;
  REG_INTERRUPT_ENABLE.raw_data &= ~(1 << number);
  REG_INTERRUPT_MASTER_ENABLE = TRUE;

  return current_handler;

}

INLINE interrupt_handler_t interrupt_add(interrupt_flag_t number,
					 interrupt_handler_t handler) {

  interrupt_handler_t current_handler = interrupt_vector[number];

  REG_INTERRUPT_MASTER_ENABLE = FALSE;
  interrupt_vector[number] = handler;
  REG_INTERRUPT_ENABLE.raw_data |= (1 << number);
  REG_INTERRUPT_MASTER_ENABLE = TRUE;

  return current_handler;

}

INLINE void interrupt_reset(void) {

  REG_INTERRUPT_MASTER_ENABLE = FALSE;
  REG_INTERRUPT_HANDLER = NULL;
  REG_INTERRUPT_ENABLE.raw_data = 0;
  //  REG_INTERRUPT_MASTER_ENABLE = TRUE;

}

INLINE void interrupt_set(interrupt_control_t enable,
			  interrupt_handler_t handler) {

  REG_INTERRUPT_MASTER_ENABLE = FALSE;
  REG_INTERRUPT_HANDLER = handler;
  REG_INTERRUPT_ENABLE = enable;
  REG_INTERRUPT_MASTER_ENABLE = TRUE;

}

INLINE void interrupt_init_default(void) {

  interrupt_control_t default_enable = { 0 };

  interrupt_set(default_enable, 
		(interrupt_handler_t)interrupt_default_handler);

}

INLINE void interrupt_init_vector(void) {

  interrupt_control_t default_enable = { 0 };

  interrupt_set(default_enable, 
		(interrupt_handler_t)interrupt_vector_handler);

}

#endif
