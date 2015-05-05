#include <immintrin.h>
#include "constants.h"
#include "limb.h"

#if !FULL_LIMB_PRECISION

    limb_t carry(limb_t a) {
        limb_t tmp = srli_limb(a, BASE_EXPONENT);
        limb_t mask = set_limb(0x1);
        return and_limb_limb(tmp, mask);
    }

    limb_t reduce_to_base_limb_t(limb_t a) {
        limb_t mask = srli_limb(set_limb(ALL_ONE), NUM_EXCESS_BASE_BITS);
        return and_limb_limb(a, mask);
    }

    limb_t excess_base_bits(limb_t a) {
        limb_t tmp = srli_limb(a, BASE_EXPONENT);
        limb_t mask = srli_limb(set_limb(ALL_ONE), NUM_EXCESS_BASE_BITS);
        return and_limb_limb(tmp, mask);
    }

    struct d_limb_t reduce_to_base_d_limb_t(struct d_limb_t a) {
        struct d_limb_t res;
        res.hi = slli_limb(a.hi, NUM_EXCESS_BASE_BITS);
        res.hi = or_limb_limb(res.hi, excess_base_bits(a.lo));
        res.lo = reduce_to_base_limb_t(a.lo);
        return res;
    }

#endif /* !FULL_LIMB_PRECISION */

limb_t zero() {
    #if SIMD_PARALLEL_WALKS

        return set_limb(0);

    #else /* SIMD_PARALLEL_WALKS */

        return 0;

    #endif /* SIMD_PARALLEL_WALKS */
}

limb_t set_limb(unsigned long long int a) {
    #if SIMD_PARALLEL_WALKS

        #if LIMB_SIZE_IN_BITS == 32

            return _mm256_set1_epi32((int) a);

        #elif LIMB_SIZE_IN_BITS == 64

            return _mm256_set1_epi64x((long long int) a);

        #endif /* LIMB_SIZE_IN_BITS */

    #else /* SIMD_PARALLEL_WALKS */

        return (limb_t) a;

    #endif /* SIMD_PARALLEL_WALKS */
}

limb_t add_limb_limb(limb_t a, limb_t b) {
    #if SIMD_PARALLEL_WALKS

        #if LIMB_SIZE_IN_BITS == 32

            return _mm256_add_epi32(a, b);

        #elif LIMB_SIZE_IN_BITS == 64

            return _mm256_add_epi64(a, b);

        #endif /* LIMB_SIZE_IN_BITS */

    #else /* SIMD_PARALLEL_WALKS */

        return a + b;

    #endif /* SIMD_PARALLEL_WALKS */
}

limb_t sub_limb_limb(limb_t a, limb_t b) {
    #if SIMD_PARALLEL_WALKS

        #if LIMB_SIZE_IN_BITS == 32

            return _mm256_sub_epi32(a, b);

        #elif LIMB_SIZE_IN_BITS == 64

            return _mm256_sub_epi64(a, b);

        #endif /* LIMB_SIZE_IN_BITS */

    #else /* SIMD_PARALLEL_WALKS */

        return a - b;

    #endif /* SIMD_PARALLEL_WALKS */
}

limb_t cmpgt_limb_limb(limb_t a, limb_t b) {
    #if SIMD_PARALLEL_WALKS

        limb_t mask = set_limb(0x1);
        limb_t tmp;

        #if LIMB_SIZE_IN_BITS == 32

            tmp = _mm256_cmpgt_epi32(a, b);

        #elif LIMB_SIZE_IN_BITS == 64

            tmp = _mm256_cmpgt_epi64(a, b);

        #endif /* LIMB_SIZE_IN_BITS */

        return and_limb_limb(tmp, mask);

    #else /* SIMD_PARALLEL_WALKS */

        return a > b;

    #endif /* SIMD_PARALLEL_WALKS */
}

limb_t cmpeq_limb_limb(limb_t a, limb_t b) {
    #if SIMD_PARALLEL_WALKS

        limb_t mask = set_limb(0x1);
        limb_t tmp;

        #if LIMB_SIZE_IN_BITS == 32

            tmp = _mm256_cmpeq_epi32(a, b);

        #elif LIMB_SIZE_IN_BITS == 64

            tmp = _mm256_cmpeq_epi64(a, b);

        #endif /* LIMB_SIZE_IN_BITS */

        return and_limb_limb(tmp, mask);

    #else /* SIMD_PARALLEL_WALKS */

        return a == b;

    #endif /* SIMD_PARALLEL_WALKS */
}

limb_t or_limb_limb(limb_t a, limb_t b) {
    #if SIMD_PARALLEL_WALKS

        return _mm256_or_si256(a, b);

    #else /* SIMD_PARALLEL_WALKS */

        return a | b;

    #endif /* SIMD_PARALLEL_WALKS */
}

limb_t and_limb_limb(limb_t a, limb_t b) {
    #if SIMD_PARALLEL_WALKS

        return _mm256_and_si256(a, b);

    #else /* SIMD_PARALLEL_WALKS */

        return a & b;

    #endif /* SIMD_PARALLEL_WALKS */
}

limb_t srli_limb(limb_t a, int b) {
    #if SIMD_PARALLEL_WALKS

        #if LIMB_SIZE_IN_BITS == 32

            return _mm256_srli_epi32(a, b);

        #elif LIMB_SIZE_IN_BITS == 64

            return _mm256_srli_epi64(a, b);

        #endif /* LIMB_SIZE_IN_BITS */

    #else /* SIMD_PARALLEL_WALKS */

        return a >> b;

    #endif /* SIMD_PARALLEL_WALKS */
}

limb_t slli_limb(limb_t a, int b) {
    #if SIMD_PARALLEL_WALKS

        #if LIMB_SIZE_IN_BITS == 32

            return _mm256_slli_epi32(a, b);

        #elif LIMB_SIZE_IN_BITS == 64

            return _mm256_slli_epi64(a, b);

        #endif /* LIMB_SIZE_IN_BITS */

    #else /* SIMD_PARALLEL_WALKS */

        return a << b;

    #endif /* SIMD_PARALLEL_WALKS */
}

limb_t load_limb(limb_t *base, unsigned int i) {
    #if SIMD_PARALLEL_WALKS

        return _mm256_load_si256(base + i);

    #else /* SIMD_PARALLEL_WALKS */

        return *(base + i);

    #endif /* SIMD_PARALLEL_WALKS */
}

void store_limb(limb_t *base, unsigned int i, limb_t data) {
    #if SIMD_PARALLEL_WALKS

        _mm256_storeu_si256(base + i, data);

    #else /* SIMD_PARALLEL_WALKS */

        *(base + i) = data;

    #endif /* SIMD_PARALLEL_WALKS */
}

struct d_limb_t mul_limb_limb(limb_t a, limb_t b) {
    struct d_limb_t c;

    #if SIMD_PARALLEL_WALKS

    #else /* SIMD_PARALLEL_WALKS */

        #if LIMB_SIZE_IN_BITS == 32

            uint64_t res = (uint64_t) a * b;
            c.lo = res & ALL_ONE;
            c.hi = (uint32_t) (res >> 32);

        #elif LIMB_SIZE_IN_BITS == 64

            #if MULX

                c.lo = _mulx_u64((unsigned long long) a, (unsigned long long) b, (unsigned long long *) &c.hi);

            #else /* MULX */

                /* -1 = 0xff..ff */
                uint32_t a_32[2] = {a & ((uint32_t) -1), (uint32_t) (a >> 32)};
                uint32_t b_32[2] = {b & ((uint32_t) -1), (uint32_t) (b >> 32)};
                uint32_t c_32[4] = {0, 0, 0, 0};

                uint64_t inner_product = 0;
                uint32_t inner_product_lo = 0;
                uint32_t inner_product_hi = 0;

                for (unsigned int i = 0; i < 2; i++) {
                    inner_product_hi = 0;
                    for (unsigned int j = 0; j < 2; j++) {
                        inner_product = c_32[i + j] + (((uint64_t) a_32[i]) * b_32[j]) + inner_product_hi;
                        inner_product_lo = inner_product & ((uint32_t) -1);
                        inner_product_hi = (uint32_t) (inner_product >> 32);
                        c_32[i + j] = inner_product_lo;
                    }
                    c_32[i + 2] = inner_product_hi;
                }

                c.lo = (((uint64_t) c_32[1]) << 32) + c_32[0];
                c.hi = (((uint64_t) c_32[3]) << 32) + c_32[2];

            #endif /* MULX */

        #endif /* LIMB_SIZE_IN_BITS */

    #endif /* SIMD_PARALLEL_WALKS */

    return c;
}
