#ifndef UTILITIES_H_
#define UTILITIES_H_

    #include <stdbool.h>
    #include <gmp.h>
    #include "gmp_int.h"
    #include "limb.h"
    #include "settings.h"
    #include "elliptic_curve.h"

    typedef struct {
        gmp_int_t big;
        gmp_int_t middle;
        gmp_int_t small;
    } three_sorted_gmp;

    typedef struct {
        void *orig;
        void *aligned;
    } aligned_memory;

    unsigned int max(unsigned int a, unsigned int b);
    unsigned int min(unsigned int a, unsigned int b);
    void print_limb(limb_t limb);
    void print_num(limb_t *num, unsigned int num_limbs);
    void print_num_gmp(gmp_int_t num_gmp, unsigned int num_limbs);
    void convert_gmp_to_num(limb_t *num, gmp_int_t num_gmp, unsigned int num_limbs);
    void convert_num_to_gmp(gmp_int_t num_gmp, limb_t *num, unsigned int num_limbs);
    bool is_equal_num_num(limb_t *num1, limb_t *num2, unsigned int num_limbs);
    bool is_equal_num_gmp(limb_t *num, gmp_int_t num_gmp, unsigned int num_limbs);
    void cmp_num_gmp(int *res, limb_t *num, gmp_int_t num_gmp, unsigned int num_limbs);
    void generate_random_gmp_less_than(gmp_int_t num_gmp, gmp_int_t strict_upper_bound_gmp, gmp_randstate_t gmp_random_state);
    void generate_random_gmp_number(gmp_int_t num_gmp, unsigned int precision_in_bits, gmp_randstate_t gmp_random_state);
    void generate_random_prime_gmp_number(gmp_int_t num_gmp, unsigned int precision_in_bits, gmp_randstate_t gmp_random_state);
    three_sorted_gmp get_three_sorted_gmp(unsigned int precision_in_bits, gmp_randstate_t gmp_random_state);
    void clear_three_sorted_gmp(three_sorted_gmp x);
    void copy_num(limb_t * const b, limb_t *a, unsigned int num_limbs);
    bool is_power_of_2(unsigned int x);
    aligned_memory alloc_aligned_memory(size_t size, unsigned int alignment_in_bytes);
    void free_aligned_memory(aligned_memory mem);
    void set_num(limb_t *num, limb_t value, unsigned int num_limbs);
    void standard_to_montgomery_representation(limb_t *num, unsigned int num_limbs);
    void montgomery_to_standard_representation(limb_t *num, unsigned int num_limbs);
    void standard_to_montgomery_representation_gmp(gmp_int_t num);
    void montgomery_to_standard_representation_gmp(gmp_int_t num);
    void standard_to_montgomery_representation_point(struct curve_point *p);
    void montgomery_to_standard_representation_point(struct curve_point *p);
    void standard_to_montgomery_representation_point_gmp(struct curve_point_gmp *p);
    void montgomery_to_standard_representation_point_gmp(struct curve_point_gmp *p);

#endif /* UTILITIES_H_ */
