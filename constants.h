#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <math.h>
#include "settings.h"

#define LIMB_SIZE_IN_BITS (64)
#define LIMB_SIZE_IN_BYTES (LIMB_SIZE_IN_BITS / 8)
#define LIMB_SIZE_IN_HEX (LIMB_SIZE_IN_BITS / 4)
#define NUM_LIMBS ((unsigned int) ceil((PRIME_FIELD_BINARY_BIT_LENGTH)/ ((double) LIMB_SIZE_IN_BITS)))
#define PRIME_FIELD_FULL_HEX_LENGTH (NUM_LIMBS * LIMB_SIZE_IN_HEX)
#define NUM_MONTGOMERY_SHIFT_LIMBS (NUM_LIMBS) // shift amount "n" in limbs such that ((n * LIMB_SIZE_IN_BITS) > PRIME_FIELD_BINARY_BIT_LENGTH) && (gcd(prime_modulus, 2^(n * LIMB_SIZE_IN_BITS)) == 1)

#if (PRIME_FIELD_BINARY_BIT_LENGTH % LIMB_SIZE_IN_BITS) == 0
#error "PRIME_FIELD_BINARY_BIT_LENGTH must not be a multiple of LIMB_SIZE_IN_BITS"
#endif

#if (PRIME_FIELD_BINARY_BIT_LENGTH < LIMB_SIZE_IN_BITS)
#error "PRIME_FIELD_BINARY_BIT_LENGTH must be larger than LIMB_SIZE_IN_BITS"
#endif

#endif
