#ifndef CONSTANTS_H_
#define CONSTANTS_H_

    #include "settings.h"

    #define BASE_EXPONENT               ((FULL_LIMB_PRECISION * LIMB_SIZE_IN_BITS) + ((!FULL_LIMB_PRECISION) * (LIMB_SIZE_IN_BITS - 1)))
    #define NUM_EXCESS_BASE_BITS        (LIMB_SIZE_IN_BITS - BASE_EXPONENT)
    #define NUM_LIMBS                   ((PRIME_FIELD_BINARY_BIT_LENGTH + BASE_EXPONENT - 1) / BASE_EXPONENT) /* equivalent to ((unsigned int) ceil((PRIME_FIELD_BINARY_BIT_LENGTH)/ ((double) BASE_EXPONENT))) */
    #define PRIME_FIELD_FULL_HEX_LENGTH (NUM_LIMBS * LIMB_SIZE_IN_HEX)

#endif /* CONSTANTS_H_ */
