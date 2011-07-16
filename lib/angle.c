#include <angle.h>

angle const ANGLE_MAX = 1 << ANGLE_FORMAT;
angle const PI        = 1 << (ANGLE_FORMAT - 1);
angle const PI_2      = 1 << (ANGLE_FORMAT - 2);
angle const PI_3_2    = 3 * (1 << (ANGLE_FORMAT - 2));
