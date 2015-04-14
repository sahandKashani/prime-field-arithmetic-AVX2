#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <math.h>
#include "settings.h"

#if BASE_2_63_REPRESENTATION
#define BASE_EXPONENT (63)
#else
#define BASE_EXPONENT (64)
#endif

#define LIMB_SIZE_IN_BITS (64)
#define LIMB_SIZE_IN_BYTES (LIMB_SIZE_IN_BITS / 8)
#define LIMB_SIZE_IN_HEX (LIMB_SIZE_IN_BITS / 4)
#define NUM_LIMBS ((unsigned int) ceil((PRIME_FIELD_BINARY_BIT_LENGTH)/ ((double) BASE_EXPONENT)))
#define PRIME_FIELD_FULL_HEX_LENGTH (NUM_LIMBS * LIMB_SIZE_IN_HEX)

#if (PRIME_FIELD_BINARY_BIT_LENGTH % LIMB_SIZE_IN_BITS) == 0
#error "PRIME_FIELD_BINARY_BIT_LENGTH must not be a multiple of LIMB_SIZE_IN_BITS"
#endif

#if (PRIME_FIELD_BINARY_BIT_LENGTH < LIMB_SIZE_IN_BITS)
#error "PRIME_FIELD_BINARY_BIT_LENGTH must be larger than LIMB_SIZE_IN_BITS"
#endif

#endif
