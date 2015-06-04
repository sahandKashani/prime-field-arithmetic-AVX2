#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
cd "${DIR}"

benchmark_dir="${DIR}/benchmarks"
rm -rf "${benchmark_dir}"
mkdir -p "${benchmark_dir}"

overwrite_file() {
    local file_content="#ifndef SETTINGS_H_
#define SETTINGS_H_

    #define PRIME_FIELD_BINARY_BIT_LENGTH       (131)
    #define LIMB_SIZE_IN_BITS                   (${limb_size_in_bits}) /* 8, 16, 32, 64 */
    #define FULL_LIMB_PRECISION                 (${full_limb_precision}) /* 0, 1 */
    #define MULX                                (${mulx}) /* 0, 1: Only useful if LIMB_SIZE_IN_BITS == 64 */
    #define SIMD_PARALLEL_WALKS                 (${simd_parallel_walks}) /* 0, 1 */
    #define TEST                                (0) /* 0, 1 */
    #define BENCHMARK_PRIME_FIELD_ARITHMETIC    (${benchmark_prime_field_arithmetic}) /* 0, 1 */
    #define BENCHMARK_ELLIPTIC_CURVE_ARITHMETIC (${benchmark_elliptic_curve_arithmetic}) /* 0, 1 */
    #define BENCHMARK_USE_GMP                   (${benchmark_use_gmp}) /* 0, 1 */

#endif /* SETTINGS_H_ */"

    echo "${file_content}" > "settings.h"
}

compile() {
    cd "${DIR}/Release"
    make clean
    make all
}

get_result_file_name() {
    if [ ${benchmark_prime_field_arithmetic} -eq 1 ]; then
        echo "primefield_${benchmark_use_gmp}_${limb_size_in_bits}_${full_limb_precision}_${mulx}_${simd_parallel_walks}"
    else
        echo "point_${benchmark_use_gmp}_${limb_size_in_bits}_${full_limb_precision}_${mulx}_${simd_parallel_walks}"
    fi
}

benchmark() {
    cd "${DIR}/Release"
    ./pollard_rho > "${benchmark_dir}/$(get_result_file_name)"
}

LIMB_SIZE_IN_BITS="8 16 32 64"
FULL_LIMB_PRECISION="0 1"
SIMD_PARALLEL_WALKS="0 1"
BENCHMARK_USE_GMP="0 1"

for limb_size_in_bits in ${LIMB_SIZE_IN_BITS}; do
    for full_limb_precision in ${FULL_LIMB_PRECISION}; do
        for simd_parallel_walks in ${SIMD_PARALLEL_WALKS}; do
            for benchmark_use_gmp in ${BENCHMARK_USE_GMP}; do
                if [ ${limb_size_in_bits} -eq 64 ] && [ ${simd_parallel_walks} -eq 0 ]; then
                    mulx="1"
                else
                    mulx="0"
                fi

                for benchmark_prime_field_arithmetic in 0 1; do
                    if [ ${benchmark_prime_field_arithmetic} -eq 0 ]; then
                        benchmark_elliptic_curve_arithmetic=1
                    else
                        benchmark_elliptic_curve_arithmetic=0
                    fi

                    overwrite_file
                    compile
                    benchmark
                done
            done
        done
    done
done
