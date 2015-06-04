#include <stdlib.h>
#include <stdio.h>
#include "compile_time_checks.h"
#include "constants.h"
#include "check_arithmetic.h"
#include "settings.h"

int main(void) {
    unsigned int number_of_points = 1 << 10;
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

    #elif BENCHMARK /* TEST */

    #endif /* BENCHMARK */

    printf("end\n");

    free_constants();
    return EXIT_SUCCESS;
}
