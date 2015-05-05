#ifndef LIMB_H_
#define LIMB_H_

    /*
     * The functions defined in this header file do perform all operations as if
     * all limbs satisfy FULL_LIMB_PRECISION == 1. Higher-level code must
     * extract carries and reduce results to the actual base used.
     */

    #include <inttypes.h>
    #include <immintrin.h>
    #include "settings.h"

    #define LIMB_SIZE_IN_BYTES (LIMB_SIZE_IN_BITS / 8)
    #define LIMB_SIZE_IN_HEX   (LIMB_SIZE_IN_BITS / 4)

    #if LIMB_SIZE_IN_BITS == 32

        typedef uint32_t limb_building_block_t;
        #define PRI_LIMB PRIx32
        #define ALL_ONE  (0xffffffff)

    #elif LIMB_SIZE_IN_BITS == 64

        typedef uint64_t limb_building_block_t;
        #define PRI_LIMB PRIx64
        #define ALL_ONE  (0xffffffffffffffffULL)

    #endif

    #if SIMD_PARALLEL_WALKS

        typedef __m256i limb_t;

    #else /* SIMD_PARALLEL_WALKS */

        typedef limb_building_block_t limb_t;

    #endif /* SIMD_PARALLEL_WALKS */

    #define NUM_ENTRIES_IN_LIMB (sizeof(limb_t) / sizeof(limb_building_block_t))

    struct d_limb_t {
        limb_t lo;
        limb_t hi;
    };

    #if !FULL_LIMB_PRECISION

        limb_t carry(limb_t a);
        limb_t reduce_to_base_limb_t(limb_t a);
        limb_t excess_base_bits(limb_t a);
        struct d_limb_t reduce_to_base_d_limb_t(struct d_limb_t a);

    #endif /* !FULL_LIMB_PRECISION */

    limb_t set_limb(unsigned long long int a);
    limb_t add_limb_limb(limb_t a, limb_t b);
    limb_t sub_limb_limb(limb_t a, limb_t b);
    limb_t cmpgt_limb_limb(limb_t a, limb_t b);
    limb_t cmpeq_limb_limb(limb_t a, limb_t b);
    limb_t or_limb_limb(limb_t a, limb_t b);
    limb_t and_limb_limb(limb_t a, limb_t b);
    limb_t srli_limb(limb_t a, int b);
    limb_t slli_limb(limb_t a, int b);
    limb_t load_limb(limb_t *base, unsigned int i);
    void store_limb(limb_t *base, unsigned int i, limb_t data);
    struct d_limb_t mul_limb_limb(limb_t a, limb_t b);

#endif /* LIMB_H_ */


