#ifndef TYPES_H_
#define TYPES_H_

/*
  COMPILER MACROS
*/

#define INLINE static inline

#define ALIGN(n)        __attribute__((aligned(n)))
#define ALIGN_CHAR      __attribute__((aligned(sizeof(char))))
#define ALIGN_HALF_WORD __attribute__((aligned(sizeof(short))))
#define ALIGN_WORD      __attribute__((aligned(sizeof(int))))
#define PACKED          __attribute__((packed))

#define IWRAM_DATA   __attribute__((section(".iwram")))
#define EWRAM_DATA   __attribute__((section(".ewram")))
#define EWRAM_BSS    __attribute__((section(".sbss")))
#define IWRAM_CODE   __attribute__((section(".iwram"), long_call))
#define EWRAM_CODE   __attribute__((section(".ewram"), long_call))

/*
  UTILITIES
*/

#define ABS(a)   ({ typeof(a) _a = a; (_a > 0) ? _a : -_a; })
#define SGN(a)   ({ typeof(a) _a = a; (_a >= 0) ? 1 : -1; })
#define MAX(a,b) ({ typeof(a) _a = a; typeof(b) _b = b; (_a > _b) ? _a : _b; })
#define MIN(a,b) ({ typeof(a) _a = a; typeof(b) _b = b; (_a > _b) ? _b : _a; })

/*
  TYPES
*/

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef volatile unsigned char  vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned int   vu32;

typedef signed char  s8;
typedef signed short s16;
typedef signed int   s32;

/*
  CONSTANTS
*/

#define NULL ((void *)0)

typedef enum bool_tag {

  FALSE = 0,
  TRUE = 1

} bool_t;

typedef enum palette_tag {

  PALETTE_4BPP = 0,
  PALETTE_8BPP = 1

} palette_t;

#endif
