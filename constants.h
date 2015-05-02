#ifndef CONSTANTS_H_
#define CONSTANTS_H_

    #include <math.h>
    #include "settings.h"

    /* compile-time checks for settings validity */
    #if LIMB_SIZE_IN_BITS != 32 && LIMB_SIZE_IN_BITS != 64
        #error "LIMB_SIZE_IN_BITS must be 32 or 64"
    #endif /* LIMB_SIZE_IN_BITS != 32 && LIMB_SIZE_IN_BITS != 64 */

    #if (PRIME_FIELD_BINARY_BIT_LENGTH % LIMB_SIZE_IN_BITS) == 0
        #error "PRIME_FIELD_BINARY_BIT_LENGTH must not be a multiple of LIMB_SIZE_IN_BITS"
    #endif /* (PRIME_FIELD_BINARY_BIT_LENGTH % LIMB_SIZE_IN_BITS) == 0 */

    #if (PRIME_FIELD_BINARY_BIT_LENGTH < LIMB_SIZE_IN_BITS)
        #error "PRIME_FIELD_BINARY_BIT_LENGTH must be larger than LIMB_SIZE_IN_BITS"
    #endif /* (PRIME_FIELD_BINARY_BIT_LENGTH < LIMB_SIZE_IN_BITS) */

    /* constants */
    #define BASE_EXPONENT               ((FULL_LIMB_PRECISION * LIMB_SIZE_IN_BITS) + ((!FULL_LIMB_PRECISION) * (LIMB_SIZE_IN_BITS - 1)))
    #define NUM_EXCESS_BASE_BITS        (LIMB_SIZE_IN_BITS - BASE_EXPONENT)
    #define NUM_LIMBS                   ((unsigned int) ceil((PRIME_FIELD_BINARY_BIT_LENGTH)/ ((double) BASE_EXPONENT)))
    #define LIMB_SIZE_IN_BYTES          (LIMB_SIZE_IN_BITS / 8)
    #define LIMB_SIZE_IN_HEX            (LIMB_SIZE_IN_BITS / 4)
    #define PRIME_FIELD_FULL_HEX_LENGTH (NUM_LIMBS * LIMB_SIZE_IN_HEX)

#endif /* CONSTANTS_H_ */
