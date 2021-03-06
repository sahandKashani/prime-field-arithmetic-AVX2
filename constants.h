#ifndef CONSTANTS_H_
#define CONSTANTS_H_

    #include "limb.h"
    #include "gmp_int.h"
    #include "settings.h"

    #define BASE_EXPONENT               ((FULL_LIMB_PRECISION * LIMB_SIZE_IN_BITS) + ((!FULL_LIMB_PRECISION) * (LIMB_SIZE_IN_BITS - 1)))
    #define NUM_EXCESS_BASE_BITS        (LIMB_SIZE_IN_BITS - BASE_EXPONENT)
    #define NUM_LIMBS                   ((PRIME_FIELD_BINARY_BIT_LENGTH + BASE_EXPONENT - 1) / BASE_EXPONENT) /* equivalent to ((unsigned int) ceil((PRIME_FIELD_BINARY_BIT_LENGTH)/ ((double) BASE_EXPONENT))) */
    #define PRIME_FIELD_FULL_HEX_LENGTH (NUM_LIMBS * LIMB_SIZE_IN_HEX)

    #define NUM_POINTS_SRC (1024) /* the points here will be used as sources to
                                     initialize a much greater pool of points */
    extern char *points_x_glo_src_hex[NUM_POINTS_SRC];
    extern char *points_y_glo_src_hex[NUM_POINTS_SRC];

    extern char *m_glo_hex;
    extern char *a_glo_hex;
    extern char *b_glo_hex;
    extern unsigned int num_points_glo;
    extern char **points_x_glo_hex; /* large pool of points */
    extern char **points_y_glo_hex; /* large pool of points */

    extern limb_t m_glo[NUM_LIMBS];
    extern limb_t a_glo[NUM_LIMBS];
    extern limb_t b_glo[NUM_LIMBS];
    extern limb_t (*points_x_glo)[NUM_LIMBS];
    extern limb_t (*points_y_glo)[NUM_LIMBS];
    extern limb_t R_2_mod_m_glo[NUM_LIMBS];
    extern limb_t m_prime_glo;
    extern limb_t inv_R_glo[NUM_LIMBS];

    extern gmp_int_t m_glo_gmp;
    extern gmp_int_t a_glo_gmp;
    extern gmp_int_t b_glo_gmp;
    extern gmp_int_t *points_x_glo_gmp;
    extern gmp_int_t *points_y_glo_gmp;
    extern gmp_int_t R_2_mod_m_glo_gmp;
    extern gmp_int_t m_prime_glo_gmp;
    extern gmp_int_t inv_R_glo_gmp;

    void initialize_constants(unsigned int num_points);
    void free_constants();

#endif /* CONSTANTS_H_ */
