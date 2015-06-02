#ifndef CONSTANTS_H_
#define CONSTANTS_H_

    #include "limb.h"
    #include "settings.h"

    #define BASE_EXPONENT               ((FULL_LIMB_PRECISION * LIMB_SIZE_IN_BITS) + ((!FULL_LIMB_PRECISION) * (LIMB_SIZE_IN_BITS - 1)))
    #define NUM_EXCESS_BASE_BITS        (LIMB_SIZE_IN_BITS - BASE_EXPONENT)
    #define NUM_LIMBS                   ((PRIME_FIELD_BINARY_BIT_LENGTH + BASE_EXPONENT - 1) / BASE_EXPONENT) /* equivalent to ((unsigned int) ceil((PRIME_FIELD_BINARY_BIT_LENGTH)/ ((double) BASE_EXPONENT))) */
    #define PRIME_FIELD_FULL_HEX_LENGTH (NUM_LIMBS * LIMB_SIZE_IN_HEX)

    extern char *m_hex_glo;
    extern char *a_hex_glo;
    extern char *b_hex_glo;

    #define NUM_POINTS (128)
    extern char *points_x_hex_glo[NUM_POINTS];
    extern char *points_y_hex_glo[NUM_POINTS];

    extern limb_t m_glo[NUM_LIMBS];
    extern limb_t R_2_mod_m_glo[NUM_LIMBS];
    extern limb_t m_prime_glo;

#endif /* CONSTANTS_H_ */
