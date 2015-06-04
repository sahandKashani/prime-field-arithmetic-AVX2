#!/bin/bash

DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
cd "${DIR}"

benchmark_dir="${DIR}/benchmarks"
rm -rf "${benchmark_dir}"
mkdir -p "${benchmark_dir}"

overwrite_file() {
    local file_content="#ifndef SETTINGS_H_
#define SETTINGS_H_

    #define PRIME_FIELD_BINARY_BIT_LENGTH        (131)
    #define LIMB_SIZE_IN_BITS                    (${limb_size_in_bits})
    #define FULL_LIMB_PRECISION                  (${full_limb_precision})
    #define MULX                                 (${mulx})
    #define SIMD_PARALLEL_WALKS                  (${simd_parallel_walks})
    #define TEST                                 (0)
    #define BENCHMARK_PRIME_FIELD_ARITHMETIC     (${benchmark_prime_field_arithmetic})
    #define BENCHMARK_ELLIPTIC_CURVE_ARITHMETIC  (${benchmark_elliptic_curve_arithmetic})

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
        echo "primefield_${limb_size_in_bits}_${full_limb_precision}_${mulx}_${simd_parallel_walks}"
    else
        echo "point_${limb_size_in_bits}_${full_limb_precision}_${mulx}_${simd_parallel_walks}"
    fi
}

benchmark() {
    cd "${DIR}/Release"
    ./pollard_rho > "${benchmark_dir}/$(get_result_file_name)"
}

LIMB_SIZE_IN_BITS="8 16 32 64"
FULL_LIMB_PRECISION="0 1"
SIMD_PARALLEL_WALKS="0 1"

for limb_size_in_bits in ${LIMB_SIZE_IN_BITS}; do
    for full_limb_precision in ${FULL_LIMB_PRECISION}; do
        for simd_parallel_walks in ${SIMD_PARALLEL_WALKS}; do
            if [ ${limb_size_in_bits} -eq 64 ] && [ ${simd_parallel_walks} -eq 0 ]; then
                mulx="1"
            else
                mulx="0"
            fi

            for config in 0 1; do
                benchmark_prime_field_arithmetic=${config}
                if [ ${benchmark_prime_field_arithmetic} -eq 0 ]; then
                    benchmark_elliptic_curve_arithmetic=1
                else
                    benchmark_elliptic_curve_arithmetic=0
                fi
            done

            overwrite_file
            compile
            benchmark
        done
    done
done
