#ifndef FIXED_H_
#define FIXED_H_

#include <types.h>
#include <bios.h>

typedef s32 sfixe;
typedef u32 ufixe;

#define FIXE_FORMAT          8
#define FIXE_FORMAT_MASK     ((1 << FIXE_FORMAT) - 1)
#define UFIXE_MAX            ((ufixe)0x0000FFFF)
#define SFIXE_MAX            ((sfixe)0x00007FFF)
#define SFIXE_MIN            ((sfixe)0xFFFF8000)

#define fixe(num,dec) ( (dec & FIXE_FORMAT_MASK) + ((num << FIXE_FORMAT) & ~FIXE_FORMAT_MASK) )
#define fint(a)       (a >> FIXE_FORMAT)
#define fmul(a,b)     ((a * b) >> FIXE_FORMAT)
#define fdiv(a,b)     ((sfixe)bios_div(a << FIXE_FORMAT, b))

#endif
