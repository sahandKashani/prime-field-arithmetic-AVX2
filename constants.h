#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <math.h>
#include <stdint.h>

#define PRIME_FIELD_BINARY_BIT_LENGTH (131)

#define LIMB_SIZE_IN_BITS (64)
#define LIMB_SIZE_IN_BYTES (LIMB_SIZE_IN_BITS / 8)
#define LIMB_SIZE_IN_HEX (LIMB_SIZE_IN_BITS / 4)
#define NUM_LIMBS ((unsigned int) ceil(PRIME_FIELD_BINARY_BIT_LENGTH / ((double) LIMB_SIZE_IN_BITS)))
#define PRIME_FIELD_FULL_HEX_LENGTH (NUM_LIMBS * LIMB_SIZE_IN_HEX)

#endif
