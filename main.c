#include <stdlib.h>
#include <stdio.h>
#include "compile_time_checks.h"
#include "constants.h"
#include "check_arithmetic.h"
#include "settings.h"

int main(void) {
    initialize_constants();

    #if TEST

        unsigned int iterations = NUMBER_OF_TESTS / NUM_ENTRIES_IN_LIMB;

        check_add_num_num(iterations, SEED);
        check_add_num_limb(iterations, SEED);
        check_sub_num_num(iterations, SEED);
        check_mul_limb_limb(iterations, SEED);
        check_mul_num_limb(iterations, SEED);
        check_mul_num_num(iterations, SEED);
        check_add_mod_num_num(iterations, SEED);
        check_sub_mod_num_num(iterations, SEED);
        check_mul_montgomery_num_num(iterations, SEED);
        check_add_point_point(iterations);
        check_double_point(iterations);
        check_neg_point(iterations);

    #elif BENCHMARK /* TEST */

    #endif /* BENCHMARK */

    printf("end\n");

    free_constants();
    return EXIT_SUCCESS;
}
