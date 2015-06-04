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
    unsigned int number_of_points = 1 << 15;
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

        struct curve_point p1;
        struct curve_point p2;
        copy_num(p1.x, points_x_glo[0], NUM_LIMBS);
        copy_num(p1.y, points_y_glo[0], NUM_LIMBS);
        copy_num(p2.x, points_x_glo[1], NUM_LIMBS);
        copy_num(p2.y, points_y_glo[1], NUM_LIMBS);

        double start = get_time();
        for (unsigned int i = 0; i < (number_of_points / NUM_ENTRIES_IN_LIMB); i++) {
            add_point_point(&p2, &p2, &p1, NUM_LIMBS);
        }
        double stop = get_time();

        printf("elapsed time = %lf s\n", stop - start);

    #elif BENCHMARK_PRIME_FIELD_ARITHMETIC /* BENCHMARK_ELLIPTIC_CURVE_ARITHMETIC */


    #endif /* BENCHMARK */

    printf("end\n");

    free_constants();
    return EXIT_SUCCESS;
}
