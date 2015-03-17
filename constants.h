#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <math.h>
#include <stdint.h>

#define PRIME_FIELD_BITS (131)

#define LIMB_SIZE_BITS (64)
#define LIMB_SIZE_BYTE (LIMB_SIZE_BITS / 8)
#define NUM_LIMBS ((unsigned int) ceil(PRIME_FIELD_BITS / ((double) LIMB_SIZE_BITS)))

#endif
