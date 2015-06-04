#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "compile_time_checks.h"
#include "constants.h"
#include "check_arithmetic.h"
#include "settings.h"
#include "elliptic_curve.h"
#include "utilities.h"

double get_time() {
    struct timeval t;
      gettimeofday(&t, NULL);
    return (double) t.tv_sec + (double) t.tv_usec*1e-6;
}

int main(void) {
    unsigned int number_of_points = 1 << 20;
    initialize_constants(number_of_points);

    #if TEST

        check_add_num_num(NUMBER_OF_TESTS, SEED);
        check_add_num_limb(NUMBER_OF_TESTS, SEED);
        check_sub_num_num(NUMBER_OF_TESTS, SEED);
        check_mul_limb_limb(NUMBER_OF_TESTS, SEED);
        check_mul_num_limb(NUMBER_OF_TESTS, SEED);
        check_mul_num_num(NUMBER_OF_TESTS, SEED);
        check_add_mod_num_num(NUMBER_OF_TESTS, SEED);
        check_sub_mod_num_num(NUMBER_OF_TESTS, SEED);
        check_mul_montgomery_num_num(NUMBER_OF_TESTS, SEED);
        check_add_point_point(number_of_points);
        check_double_point(number_of_points);
        check_neg_point(number_of_points);

    #elif BENCHMARK_ELLIPTIC_CURVE_ARITHMETIC /* TEST */

        double start = 0;
        double stop = 0;

        #if BENCHMARK_USE_GMP

            struct curve_point_gmp p1_gmp;
            struct curve_point_gmp p2_gmp;
            curve_point_init_gmp(&p1_gmp);
            curve_point_init_gmp(&p2_gmp);

            gmp_int_set(p1_gmp.x, points_x_glo_gmp[0]);
            gmp_int_set(p1_gmp.y, points_y_glo_gmp[0]);
            gmp_int_set(p2_gmp.x, points_x_glo_gmp[1]);
            gmp_int_set(p2_gmp.y, points_y_glo_gmp[1]);

            start = get_time();
            for (unsigned int i = 0; i < (number_of_points / NUM_ENTRIES_IN_LIMB); i++) {
                add_point_point_gmp(&p2_gmp, &p2_gmp, &p1_gmp);
            }
            stop = get_time();
            printf("add_point_point_gmp = %lf s\n", stop - start);

            start = get_time();
            for (unsigned int i = 0; i < (number_of_points / NUM_ENTRIES_IN_LIMB); i++) {
                neg_point_gmp(&p1_gmp, &p1_gmp);
            }
            stop = get_time();
            printf("neg_point_gmp = %lf s\n", stop - start);

            start = get_time();
            for (unsigned int i = 0; i < (number_of_points / NUM_ENTRIES_IN_LIMB); i++) {
                double_point_gmp(&p1_gmp, &p1_gmp);
            }
            stop = get_time();
            printf("double_point_gmp = %lf s\n", stop - start);

        #else

            struct curve_point p1;
            struct curve_point p2;
            copy_num(p1.x, points_x_glo[0], NUM_LIMBS);
            copy_num(p1.y, points_y_glo[0], NUM_LIMBS);
            copy_num(p2.x, points_x_glo[1], NUM_LIMBS);
            copy_num(p2.y, points_y_glo[1], NUM_LIMBS);

            start = get_time();
            for (unsigned int i = 0; i < (number_of_points / NUM_ENTRIES_IN_LIMB); i++) {
                add_point_point(&p2, &p2, &p1, NUM_LIMBS);
            }
            stop = get_time();
            printf("add_point_point = %lf s\n", stop - start);

            start = get_time();
            for (unsigned int i = 0; i < (number_of_points / NUM_ENTRIES_IN_LIMB); i++) {
                neg_point(&p1, &p1, NUM_LIMBS);
            }
            stop = get_time();
            printf("neg_point = %lf s\n", stop - start);

            start = get_time();
            for (unsigned int i = 0; i < (number_of_points / NUM_ENTRIES_IN_LIMB); i++) {
                double_point(&p1, &p1, NUM_LIMBS);
            }
            stop = get_time();
            printf("double_point = %lf s\n", stop - start);

        #endif /* BENCHMARK_USE_GMP */

    #elif BENCHMARK_PRIME_FIELD_ARITHMETIC /* BENCHMARK_ELLIPTIC_CURVE_ARITHMETIC */

        double start = 0;
        double stop = 0;

    #endif /* BENCHMARK */

    free_constants();
    return EXIT_SUCCESS;
}
