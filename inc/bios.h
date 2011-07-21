#ifndef BIOS_H_
#define BIOS_H_

#include <types.h>

enum {

  BIOS_SOFT_RESET = 0,
  BIOS_REGISTER_RAM_RESET,
  BIOS_HALT,
  BIOS_STOP,
  BIOS_INTERRUPT_WAIT,
  BIOS_VBLANK_INTERRUPT_WAIT,
  BIOS_DIV,
  BIOS_DIV_ARM,
  BIOS_SQRT,
  BIOS_ARCTAN,
  BIOS_ARCTAN2,
  BIOS_CPU_SET,
  BIOS_CPU_FAST_SET,
  BIOS_CHECKSUM,
  BIOS_BG_AFFINE_SET,
  BIOS_OBJ_AFFINE_SET,
  BIOS_BIT_UNPACK,
  BIOS_LZ77_UNCOMPRESS_WRAM,
  BIOS_LZ77_UNCOMPRESS_VRAM,
  BIOS_HUFFMAN_UNCOMPRESS,
  BIOS_RLE_UNCOMPRESS_WRAM,
  BIOS_RLE_UNCOMPRESS_VRAM,
  BIOS_DIFF_8BIT_UNFILTER_WRAM,
  BIOS_DIFF_8BIT_UNFILTER_VRAM,
  BIOS_DIFF_16BIT_UNFILTER,
  BIOS_SOUND_BIAS_CHANGE,
  BIOS_SOUND_DRIVER_INIT,
  BIOS_SOUND_DRIVER_MODE,
  BIOS_SOUND_DRIVER_MAIN,
  BIOS_SOUND_DRIVER_VSYNC,
  BIOS_SOUND_CHANNEL_CLEAR,
  BIOS_MIDIKEY_TO_FREQ,
  BIOS_SOUND_WHATEVER0,
  BIOS_SOUND_WHATEVER1,
  BIOS_SOUND_WHATEVER2,
  BIOS_SOUND_WHATEVER3,
  BIOS_SOUND_WHATEVER4,
  BIOS_MULTIBOOT,
  BIOS_HARD_RESET,
  BIOS_CUSTOM_HALT,
  BIOS_SOUND_DRIVER_VSYNC_OFF,
  BIOS_SOUND_DRIVER_VSYNC_ON,
  BIOS_SOUND_GET_JUMPLIST,
  BIOS_NB,

};

#ifdef __thumb__
#define bios_call(x)  asm volatile("swi\t"#x ::: "r0", "r1", "r2", "r3")
#else
#define bios_call(x)  asm volatile("swi\t"#x"<<16" ::: "r0", "r1", "r2", "r3")
#endif

s32 bios_div(s32 num, s32 den);
u16 bios_sqrt(u32 num);
u16 bios_atan2(s16 X, s16 Y);
void bios_wait_vsync(void);

typedef struct bios_bg_affine_tag {

  s32 map_anchor_x;
  s32 map_anchor_y;
  s16 screen_anchor_x;
  s16 screen_anchor_y;
  s16 scale_x;
  s16 scale_y;
  u16 rotation;

} PACKED ALIGN_HALF_WORD bios_bg_affine_t;

typedef struct bios_obj_affine_tag {

  s16 scale_x;
  s16 scale_y;
  u16 rotation;

} PACKED ALIGN_HALF_WORD bios_obj_affine_t;

void bios_bg_affine_set(bios_bg_affine_t *src,
			void *dst,
			u32 num_elements);
void bios_obj_affine_set(bios_obj_affine_t *src,
			 void *dst,
			 u32 num_elements,
			 u32 offset);

#endif
