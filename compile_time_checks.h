#ifndef COMPILE_TIME_CHECKS_H_
#define COMPILE_TIME_CHECKS_H_

    #include "settings.h"

    /* compile-time checks for settings validity */
    #if LIMB_SIZE_IN_BITS != 16 && LIMB_SIZE_IN_BITS != 32 && LIMB_SIZE_IN_BITS != 64

        #error "LIMB_SIZE_IN_BITS must be 16, 32 or 64"

    #endif /* LIMB_SIZE_IN_BITS != 32 && LIMB_SIZE_IN_BITS != 64 */

    #if (PRIME_FIELD_BINARY_BIT_LENGTH % LIMB_SIZE_IN_BITS) == 0

        #error "PRIME_FIELD_BINARY_BIT_LENGTH must not be a multiple of LIMB_SIZE_IN_BITS"

    #endif /* (PRIME_FIELD_BINARY_BIT_LENGTH % LIMB_SIZE_IN_BITS) == 0 */

    #if (PRIME_FIELD_BINARY_BIT_LENGTH < LIMB_SIZE_IN_BITS)

        #error "PRIME_FIELD_BINARY_BIT_LENGTH must be larger than LIMB_SIZE_IN_BITS"

    #endif /* (PRIME_FIELD_BINARY_BIT_LENGTH < LIMB_SIZE_IN_BITS) */

#endif /* COMPILE_TIME_CHECKS_H_ */
