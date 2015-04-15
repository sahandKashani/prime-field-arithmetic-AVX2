#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "utilities.h"
#include "constants.h"
#include "prime_field_arithmetic.h"

unsigned int max(unsigned int a, unsigned int b) {
    return (a > b) ? a : b;
}

unsigned int min(unsigned int a, unsigned int b) {
    return (a < b) ? a : b;
}

void print_num(uint64_t const * const num, unsigned int const num_limbs) {
    for (unsigned int i = 0; i < num_limbs; i++) {
        printf("%0*" PRIx64 " ", LIMB_SIZE_IN_HEX, num[num_limbs - i - 1]);
    }
    printf("\n");
}

void print_num_gmp(mpz_t const num_gmp, unsigned int const num_limbs) {
    uint64_t tmp[num_limbs];
    convert_gmp_to_num(tmp, num_gmp, num_limbs);
    print_num(tmp, num_limbs);
}

void clear_num(uint64_t * const num, unsigned int const num_limbs) {
    for (unsigned int i = 0; i < num_limbs; i++) {
        num[i] = 0;
    }
}

void convert_gmp_to_num(uint64_t * const num, mpz_t const num_gmp, unsigned int const num_limbs) {
    // must clear the number, because GMP will only fill enough words that is
    // needed, so the last words of num may not be set automatically.
    clear_num(num, num_limbs);
    mpz_export(num, NULL, -1, LIMB_SIZE_IN_BYTES, 0, LIMB_SIZE_IN_BITS - BASE_EXPONENT, num_gmp);
}

void convert_num_to_gmp(mpz_t num_gmp, uint64_t const * const num, unsigned int const num_limbs) {
    mpz_import(num_gmp, num_limbs, -1, LIMB_SIZE_IN_BYTES, 0, LIMB_SIZE_IN_BITS - BASE_EXPONENT, num);
}

bool is_equal_num_num(uint64_t const * const num1, uint64_t const * const num2, unsigned int const num_limbs) {
    for (unsigned int i = 0; i < num_limbs; i++) {
        if (num1[i] != num2[i]) {
            return false;
        }
    }
    return true;
}

bool is_equal_num_gmp(uint64_t const * const num, mpz_t const num_gmp, unsigned int const num_limbs) {
    return cmp_num_gmp(num, num_gmp, num_limbs) == 0;
}

int cmp_num_gmp(uint64_t const * const num, mpz_t const num_gmp, unsigned int const num_limbs) {
    mpz_t tmp;
    mpz_init(tmp);
    convert_num_to_gmp(tmp, num, num_limbs);
    int result = mpz_cmp(tmp, num_gmp);
    mpz_clear(tmp);
    return result;
}

void generate_random_gmp_less_than(mpz_t num_gmp, mpz_t strict_upper_bound_gmp, gmp_randstate_t gmp_random_state) {
    mpz_urandomm(num_gmp, gmp_random_state, strict_upper_bound_gmp);
}

void generate_random_gmp_number(mpz_t num_gmp, unsigned int const precision_in_bits, gmp_randstate_t gmp_random_state) {
    // random number with long chain of consecutive 0s and 1s for testing
    mpz_rrandomb(num_gmp, gmp_random_state, precision_in_bits);
}

void generate_random_prime_gmp_number(mpz_t num_gmp, unsigned int const precision_in_bits, gmp_randstate_t gmp_random_state) {
    do {
        // finding a random prime number with a long chain of 0s and 1s is hard,
        // so we use a more "general" random number
        mpz_urandomb(num_gmp, gmp_random_state, precision_in_bits);
    } while (mpz_probab_prime_p(num_gmp, 25) == 0); // definitely not composite
}

three_sorted_gmp get_three_sorted_gmp(unsigned int precision_in_bits, gmp_randstate_t gmp_random_state) {
    three_sorted_gmp output;
    mpz_init(output.big);
    mpz_init(output.middle);
    mpz_init(output.small);

    do {
        generate_random_gmp_number(output.big, precision_in_bits, gmp_random_state);
        generate_random_gmp_number(output.middle, precision_in_bits, gmp_random_state);
        generate_random_gmp_number(output.small, precision_in_bits, gmp_random_state);
    } while ((mpz_cmp(output.big, output.middle) == 0) || (mpz_cmp(output.big, output.small) == 0) || (mpz_cmp(output.middle, output.small) == 0));

    // How to sort 3 values in descending order (a > b > c)
    //  if (a > b) swap(a, b)
    //  if (a > c) swap(a, c)
    //  if (b > c) swap(b, c);
    if (mpz_cmp(output.small, output.middle) == 1) mpz_swap(output.small, output.middle);
    if (mpz_cmp(output.small, output.big) == 1) mpz_swap(output.small, output.big);
    if (mpz_cmp(output.middle, output.big) == 1) mpz_swap(output.middle, output.big);

    return output;
}

void clear_three_sorted_gmp(three_sorted_gmp x) {
    mpz_clear(x.big);
    mpz_clear(x.middle);
    mpz_clear(x.small);
}

void copy_num(uint64_t * const b, uint64_t const * const a, unsigned int const num_limbs) {
    for (unsigned int i = 0; i < num_limbs; i++) {
        b[i] = a[i];
    }
}

bool is_power_of_2(unsigned int x) {
    return x && !(x & (x - 1));
}

aligned_memory alloc_aligned_memory(size_t size, unsigned int alignment_in_bytes) {
    assert(is_power_of_2(alignment_in_bytes));
    aligned_memory mem;

    mem.orig = malloc(size + alignment_in_bytes - 1);
    assert(mem.orig != NULL);

    uintptr_t mask = (uintptr_t) (alignment_in_bytes - 1);
    mem.aligned = (void *) (((uintptr_t) mem.orig + alignment_in_bytes - 1) & ~mask);

    return mem;
}

void free_aligned_memory(aligned_memory mem) {
    free(mem.orig);
}
