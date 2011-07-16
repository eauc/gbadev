#ifndef ANGLE_H_
#define ANGLE_H_

#include <fixed.h>

typedef s32 angle;

#define ANGLE_FORMAT          16
#define ANGLE_FORMAT_MASK     ((1 << ANGLE_FORMAT) - 1)

extern angle const ANGLE_MAX;
extern angle const PI;
extern angle const PI_2;
extern angle const PI_3_2;

#define LUT_SIN_FORMAT         8
#define LUT_SIN_INDICE_RANGE   9
#define LUT_SIN_OFFSET         (ANGLE_FORMAT - LUT_SIN_INDICE_RANGE - 2)
extern u8 lut_sin[];

#define smul(a,s)     ((a * s) >> LUT_SIN_FORMAT)

INLINE angle angle_format(angle t) {

  if(0 <= t) {

    return (t & ANGLE_FORMAT_MASK);

  }
  else {
    
    return (ANGLE_MAX - ( (-t) & ANGLE_FORMAT_MASK ));

  }

}

INLINE sfixe sinus(angle t) {

  t = angle_format(t);
  if(0 == t) {

    return 0;

  }
  else if(PI_2 >= t) {

    return lut_sin[(t >> LUT_SIN_OFFSET) - 1] + 1;

  }
  else if(PI == t) {

    return 0;

  }
  else if(PI >= t) {

    t = (PI - t);
    return lut_sin[(t >> LUT_SIN_OFFSET) - 1] + 1;

  }
  else if(PI_3_2 > t) {

    t = (t - PI);
    return -lut_sin[(t >> LUT_SIN_OFFSET) - 1] - 1;

  }
  else {

    t = (ANGLE_MAX - t);
    return -lut_sin[(t >> LUT_SIN_OFFSET) - 1] - 1;

  }

}

INLINE sfixe cosinus(angle t) {

  t = angle_format(t);
  if(PI_2 > t) {

    t = (PI_2 - t);
    return lut_sin[(t >> LUT_SIN_OFFSET) - 1] + 1;

  }
  else if(PI_2 == t) {

    return 0;

  }
  else if(PI >= t) {

    t = (t - PI_2);
    return -lut_sin[(t >> LUT_SIN_OFFSET) - 1] - 1;

  }
  else if(PI_3_2 > t) {

    t = (PI_3_2 - t);
    return -lut_sin[(t >> LUT_SIN_OFFSET) - 1] - 1;

  }
  else if(PI_3_2 == t) {

    return 0;

  }
  else {

    t = (t - PI_3_2);
    return lut_sin[(t >> LUT_SIN_OFFSET) - 1] + 1;

  }

}

#endif
