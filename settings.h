#ifndef SETTINGS_H_
#define SETTINGS_H_

    #define PRIME_FIELD_BINARY_BIT_LENGTH       (131)
    #define LIMB_SIZE_IN_BITS                   (8) /* 8, 16, 32, 64 */
    #define FULL_LIMB_PRECISION                 (0) /* 0, 1 */
    #define MULX                                (0) /* 0, 1: Only useful if LIMB_SIZE_IN_BITS == 64 */
    #define SIMD_PARALLEL_WALKS                 (0) /* 0, 1 */
    #define TEST                                (0) /* 0, 1 */
    #define BENCHMARK_PRIME_FIELD_ARITHMETIC    (1) /* 0, 1 */
    #define BENCHMARK_ELLIPTIC_CURVE_ARITHMETIC (0) /* 0, 1 */
    #define BENCHMARK_USE_GMP                   (0) /* 0, 1 */

#endif /* SETTINGS_H_ */
