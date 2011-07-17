#ifndef DMA_H_
#define DMA_H_

#include <mem.h>
#include <types.h>

enum {

  DMA_ADJ_INCREMENT = 0x00,
  DMA_ADJ_DECREMENT = 0x01,
  DMA_ADJ_FIXED = 0x02,
  DMA_ADJ_RELOAD = 0x03,

};

enum {

  DMA_16 = 0,
  DMA_32 = 1,

};

enum {

  DMA_NOW = 0x00,
  DMA_AT_VBLANK = 0x01,
  DMA_AT_HBLANK = 0x02,
  DMA_AT_REFRESH = 0x03,

};

typedef vu16 dma_count_t;

typedef union dma_control_tag {

  vu16 raw_data;
  struct {

  vu16 /* unused */:5;
    vu16 dst_adjust:2;
    vu16 src_adjust:2;
    vu16 repeat:1;
    vu16 chunk_size:1;
  vu16 /* unused */:1;
    vu16 timing_mode:2;
    vu16 enable_irq:1;
    vu16 enable:1;

  };

} PACKED ALIGN_HALF_WORD dma_control_t;

typedef struct dma_tag {

  void const *src;
  void *dst;
  dma_count_t count;
  dma_control_t control;

} PACKED ALIGN_WORD dma_t;

#define REG_DMA  ((dma_t *) (MEM_IO + 0x00B0))

INLINE void dma_cpy(void *dst,
		    void const *src,
		    u32 size,
		    u32 channel,
		    u32 chunk_size) {

  dma_control_t temp = { 0, };

  REG_DMA[channel].control.raw_data = 0;
  REG_DMA[channel].src = src;
  REG_DMA[channel].dst = dst;
  REG_DMA[channel].count = size >> (1 + chunk_size);
  /* temp.dst_adjust = DMA_ADJ_INCREMENT; */
  /* temp.src_adjust = DMA_ADJ_INCREMENT; */
  /* temp.repeat = DMA_NOW; */
  temp.chunk_size = chunk_size;
  /* temp.timing_mode = DMA_NOW; */
  /* temp.enable_irq = FALSE; */
  temp.enable = TRUE;
  REG_DMA[channel].control.raw_data = temp.raw_data;
  REG_DMA[channel].control.raw_data = 0;

}

INLINE void dma_hblank(void *dst,
		       void *src,
		       u32 size,
		       u32 channel,
		       u32 chunk_size,
		       u32 src_adjust) {

  dma_control_t temp = { 0, };

  REG_DMA[channel].control.raw_data = 0;

  temp.dst_adjust = DMA_ADJ_RELOAD;
  temp.src_adjust = src_adjust;
  temp.repeat = TRUE;
  temp.chunk_size = chunk_size;
  temp.timing_mode = DMA_AT_HBLANK;
  temp.enable_irq = FALSE;
  temp.enable = TRUE;

  REG_DMA[channel].count = size >> (1 + chunk_size);
  REG_DMA[channel].dst = dst;
  REG_DMA[channel].src = src;
  REG_DMA[channel].control.raw_data = temp.raw_data;

}

void dma_set32(void *dst,
	       volatile u32 src,
	       u32 size,
	       u32 channel);

void dma_set16(void *dst,
	       volatile u16 src,
	       u32 size,
	       u32 channel);

#endif

