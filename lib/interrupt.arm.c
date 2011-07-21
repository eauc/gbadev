#include <interrupt.h>
#include <m3.h>

interrupt_handler_t interrupt_vector[INTERRUPT_NB] = { NULL, };

IWRAM_CODE void interrupt_default_handler(void) {

  interrupt_control_t raised_interrupts;

  raised_interrupts.raw_data = REG_INTERRUPT_FLAG.raw_data 
    & REG_INTERRUPT_ENABLE.raw_data;

  REG_INTERRUPT_FLAG_BIOS.raw_data |= raised_interrupts.raw_data;
  REG_INTERRUPT_FLAG.raw_data = raised_interrupts.raw_data;


}

IWRAM_CODE void interrupt_vector_handler(void) {

  interrupt_control_t raised_interrupts;
  u32 i;

  raised_interrupts.raw_data = REG_INTERRUPT_FLAG.raw_data 
    & REG_INTERRUPT_ENABLE.raw_data;

  REG_INTERRUPT_FLAG_BIOS.raw_data |= raised_interrupts.raw_data;
  REG_INTERRUPT_FLAG.raw_data = raised_interrupts.raw_data;

  for(i = 0 ; i < INTERRUPT_NB ; i++) {

    if(NULL != interrupt_vector[i] &&
       ( (1 << i) & raised_interrupts.raw_data )) {

      interrupt_vector[i]();

    }

  }

}
