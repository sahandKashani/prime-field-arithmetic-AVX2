#include <immintrin.h>
#include "constants.h"
#include "limb.h"

limb_t set_limb(unsigned long long int a) {
    #if SIMD_PARALLEL_WALKS

        #if LIMB_SIZE_IN_BITS == 32

            return _mm256_set1_epi32((int) a);

        #elif LIMB_SIZE_IN_BITS == 64

            return _mm256_set1_epi64x((long long int) a);

        #endif

    #else

        return (limb_t) a;

    #endif
}

limb_t add_limb_limb(limb_t a, limb_t b) {
    #if SIMD_PARALLEL_WALKS

        #if LIMB_SIZE_IN_BITS == 32

            return _mm256_add_epi32(a, b);

        #elif LIMB_SIZE_IN_BITS == 64

            return _mm256_add_epi64(a, b);

        #endif

    #else

        return a + b;

    #endif
}

limb_t sub_limb_limb(limb_t a, limb_t b) {
    #if SIMD_PARALLEL_WALKS

        #if LIMB_SIZE_IN_BITS == 32

            return _mm256_sub_epi32(a, b);

        #elif LIMB_SIZE_IN_BITS == 64

            return _mm256_sub_epi64(a, b);

        #endif

    #else

        return a - b;

    #endif
}

limb_t cmpgt_limb_limb(limb_t a, limb_t b) {
    #if SIMD_PARALLEL_WALKS

        limb_t mask = set(0x1);
        limb_t tmp;

        #if LIMB_SIZE_IN_BITS == 32

            tmp = _mm256_cmpgt_epi32(a, b);

        #elif LIMB_SIZE_IN_BITS == 64

            tmp = _mm256_sub_epi64(a, b);

        #endif

        return and(tmp, mask);

    #else

        return a > b;

    #endif
}

limb_t or_limb_limb(limb_t a, limb_t b) {
    #if SIMD_PARALLEL_WALKS

        return _mm256_or_si256(a, b);

    #else

        return a | b;

    #endif
}

limb_t and_limb_limb(limb_t a, limb_t b) {
    #if SIMD_PARALLEL_WALKS

        return _mm256_and_si256(a, b);

    #else

        return a & b;

    #endif
}

limb_t srli_limb(limb_t a, unsigned int b) {
    #if SIMD_PARALLEL_WALKS

        #if LIMB_SIZE_IN_BITS == 32

            return _mm256_srli_epi32(a, b);

        #elif LIMB_SIZE_IN_BITS == 64

            return _mm256_srli_epi64(a, b);

        #endif

    #else

        return a >> b;

    #endif
}

limb_t load_limb(limb_t *base, unsigned int i) {
    #if SIMD_PARALLEL_WALKS

        return _mm256_load_si256(base + i);

    #else

        return *(base + i);

    #endif
}

void store_limb(limb_t *base, unsigned int i, limb_t data) {
    #if SIMD_PARALLEL_WALKS

        _mm256_storeu_si256(base + i, data);

    #else

        *(base + i) = data;

    #endif
}

void mul_limb_limb(limb_t *c_hi, limb_t *c_lo, limb_t a, limb_t b) {
    #if LIMB_SIZE_IN_BITS == 32

        uint64_t res = (uint64_t) a * b;
        *c_lo = res & ((uint32_t) -1);
        *c_hi = (uint32_t) (res >> 32);

    #elif LIMB_SIZE_IN_BITS == 64

        #if MULX

            *c_lo = _mulx_u64((unsigned long long) a, (unsigned long long) b, (unsigned long long *) c_hi);

        #else

            // -1 = 0xff..ff
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

            *c_lo = (((uint64_t) c_32[1]) << 32) + c_32[0];
            *c_hi = (((uint64_t) c_32[3]) << 32) + c_32[2];

        #endif // MULX

    #endif // LIMB_SIZE_IN_BITS

    #if !FULL_LIMB_PRECISION

        *c_hi <<= NUM_EXCESS_BASE_BITS;
        *c_hi |= excess_base_bits(*c_lo);
        *c_lo = reduce_to_base(*c_lo);

    #endif
}
