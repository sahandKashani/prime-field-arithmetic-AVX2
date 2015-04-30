#ifndef LIMB_H_
#define LIMB_H_

    #include <inttypes.h>
    #include <immintrin.h>
    #include "settings.h"

    #if LIMB_SIZE_IN_BITS == 32

        #define PRI_LIMB PRIx32
        #define ALL_ONE (0xffffffff)

    #elif LIMB_SIZE_IN_BITS == 64

        #define PRI_LIMB PRIx64
        #define ALL_ONE (0xffffffffffffffffULL)

    #endif // LIMB_SIZE_IN_BITS

    #if SIMD_PARALLEL_WALKS

        typedef __m256i limb_t;

    #else // SIMD_PARALLEL_WALKS

        #if LIMB_SIZE_IN_BITS == 32

            typedef uint32_t limb_t;

        #elif LIMB_SIZE_IN_BITS == 64

            typedef uint64_t limb_t;

        #endif // LIMB_SIZE_IN_BITS

    #endif // SIMD_PARALLEL_WALKS

    #if !FULL_LIMB_PRECISION

        limb_t carry(limb_t limb);
        limb_t reduce_to_base(limb_t limb);
        limb_t excess_base_bits(limb_t limb);

    #endif // !FULL_LIMB_PRECISION

    limb_t set_limb(unsigned long long int a);
    limb_t add_limb_limb(limb_t a, limb_t b);
    limb_t sub_limb_limb(limb_t a, limb_t b);
    limb_t cmpgt_limb_limb(limb_t a, limb_t b);
    limb_t or_limb_limb(limb_t a, limb_t b);
    limb_t and_limb_limb(limb_t a, limb_t b);
    limb_t srli_limb(limb_t a, int b);
    limb_t slli_limb(limb_t a, int b);
    limb_t load_limb(limb_t *base, unsigned int i);
    void store_limb(limb_t *base, unsigned int i, limb_t data);
    void mul_limb_limb(limb_t *c_hi, limb_t *c_lo, limb_t a, limb_t b);

#endif // LIMB_H_
