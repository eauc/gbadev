#include <dma.h>

/* DO NOT INLINE */
void dma_set32(void *dst,
	       volatile u32 src,
	       u32 size,
	       u32 channel) {

  dma_control_t temp = { 0, };

  REG_DMA[channel].control.raw_data = 0;
  REG_DMA[channel].src = (void const *)&src;
  REG_DMA[channel].dst = dst;
  REG_DMA[channel].count = size >> 2;
  /* temp.dst_adjust = DMA_ADJ_INCREMENT; */
  temp.src_adjust = DMA_ADJ_FIXED;
  /* temp.repeat = DMA_NOW; */
  temp.chunk_size = DMA_32;
  /* temp.timing_mode = DMA_NOW; */
  /* temp.enable_irq = FALSE; */
  temp.enable = TRUE;
  REG_DMA[channel].control.raw_data = temp.raw_data;

}

/* DO NOT INLINE */
void dma_set16(void *dst,
	       volatile u16 src,
	       u32 size,
	       u32 channel) {

  dma_control_t temp = { 0, };

  REG_DMA[channel].control.raw_data = 0;
  REG_DMA[channel].src = (void const *)&src;
  REG_DMA[channel].dst = dst;
  REG_DMA[channel].count = size >> 1;
  /* temp.dst_adjust = DMA_ADJ_INCREMENT; */
  temp.src_adjust = DMA_ADJ_FIXED;
  /* temp.repeat = DMA_NOW; */
  temp.chunk_size = DMA_16;
  /* temp.timing_mode = DMA_NOW; */
  /* temp.enable_irq = FALSE; */
  temp.enable = TRUE;
  REG_DMA[channel].control.raw_data = temp.raw_data;

}

