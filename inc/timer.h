#ifndef TIMER_H_
#define TIMER_H_

enum {

  TIMER_FREQ_1 = 0x00,
  TIMER_FREQ_64 = 0x01,
  TIMER_FREQ_256 = 0x02,
  TIMER_FREQ_1024 = 0x03,

};

typedef struct timer_control_tag {

  vu16 frequency:2;
  vu16 cascade:1;
vu16 /*unused*/:3;
  vu16 enable_irq:1;
  vu16 enable:1;
vu16 /*unused*/:8;

} ALIGN_HALF_WORD timer_control_t;

typedef struct timer_tag {

  vu16 data;
  timer_control_t control;

} PACKED ALIGN_WORD timer_t;

#define REG_TIMER ((timer_t *)(MEM_IO + 0x0100))

#endif
