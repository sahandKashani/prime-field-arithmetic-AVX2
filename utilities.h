#ifndef UTILITIES_H_
#define UTILITIES_H_

    #include <stdbool.h>
    #include <gmp.h>
    #include "limb.h"
    #include "settings.h"

    typedef struct {
        mpz_t big;
        mpz_t middle;
        mpz_t small;
    } three_sorted_gmp;

    typedef struct {
        void *orig;
        void *aligned;
    } aligned_memory;

    unsigned int max(unsigned int a, unsigned int b);
    unsigned int min(unsigned int a, unsigned int b);
    void print_num(limb_t const * const num, unsigned int const num_limbs);
    void print_num_gmp(mpz_t const num_gmp, unsigned int const num_limbs);
    void clear_num(limb_t * const num, unsigned int const num_limbs);
    void convert_gmp_to_num(limb_t * const num, mpz_t const num_gmp, unsigned int const num_limbs);
    void convert_num_to_gmp(mpz_t num_gmp, limb_t const * const num, unsigned int const num_limbs);
    bool is_equal_num_num(limb_t const * const num1, limb_t const * const num2, unsigned int const num_limbs);
    bool is_equal_num_gmp(limb_t const * const num, mpz_t const num_gmp, unsigned int const num_limbs);
    int cmp_num_gmp(limb_t const * const num, mpz_t const num_gmp, unsigned int const num_limbs);
    void generate_random_gmp_less_than(mpz_t num_gmp, mpz_t strict_upper_bound_gmp, gmp_randstate_t gmp_random_state);
    void generate_random_gmp_number(mpz_t num_gmp, unsigned int const precision_in_bits, gmp_randstate_t gmp_random_state);
    void generate_random_prime_gmp_number(mpz_t num_gmp, unsigned int const precision_in_bits, gmp_randstate_t gmp_random_state);
    three_sorted_gmp get_three_sorted_gmp(unsigned int precision_in_bits, gmp_randstate_t gmp_random_state);
    void clear_three_sorted_gmp(three_sorted_gmp x);
    void copy_num(limb_t * const b, limb_t const * const a, unsigned int const num_limbs);
    bool is_power_of_2(unsigned int x);
    aligned_memory alloc_aligned_memory(size_t size, unsigned int alignment_in_bytes);
    void free_aligned_memory(aligned_memory mem);

#endif // UTILITIES_H_
