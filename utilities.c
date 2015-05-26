#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "arithmetic.h"
#include "constants.h"
#include "gmp_int.h"
#include "limb.h"
#include "utilities.h"

limb_building_block_t extract_limb(limb_t *num, unsigned int limb_index, unsigned int entry_in_limb_index, unsigned int num_entries_in_limb) {
    limb_building_block_t *num_internal_format = (limb_building_block_t *) num;
    return *(num_internal_format + (limb_index * num_entries_in_limb) + entry_in_limb_index);
}

void transpose_num(limb_building_block_t *num_internal_format, unsigned int num_limbs, unsigned int num_entries_in_limb) {
    limb_building_block_t tmp[num_limbs * num_entries_in_limb];

    /* copy num to tmp */
    for (unsigned int limb_index = 0; limb_index < num_limbs; limb_index++) {
        for (unsigned int entry_in_limb_index = 0; entry_in_limb_index < num_entries_in_limb; entry_in_limb_index++) {
            tmp[(limb_index * num_entries_in_limb) + entry_in_limb_index] = *(num_internal_format + (limb_index * num_entries_in_limb) + entry_in_limb_index);
        }
    }

    /* transpose */
    for (unsigned int limb_index = 0; limb_index < num_limbs; limb_index++) {
        for (unsigned int entry_in_limb_index = 0; entry_in_limb_index < num_entries_in_limb; entry_in_limb_index++) {
            *(num_internal_format + (entry_in_limb_index * num_limbs) + limb_index) = tmp[(limb_index * num_entries_in_limb) + entry_in_limb_index];
        }
    }
}

unsigned int max(unsigned int a, unsigned int b) {
    return (a > b) ? a : b;
}

unsigned int min(unsigned int a, unsigned int b) {
    return (a < b) ? a : b;
}

void print_limb(limb_t limb) {
    printf("| ");
    for (unsigned int entry_in_limb_index = 0; entry_in_limb_index < NUM_ENTRIES_IN_LIMB; entry_in_limb_index++) {
        printf("%0*" PRI_LIMB " | ", LIMB_SIZE_IN_HEX, extract_limb(&limb, 0, entry_in_limb_index, NUM_ENTRIES_IN_LIMB));
    }
    printf("\n");
}

void print_num(limb_t *num, unsigned int num_limbs) {
    for (unsigned int entry_in_limb_index = 0; entry_in_limb_index < NUM_ENTRIES_IN_LIMB; entry_in_limb_index++) {
        if (entry_in_limb_index == 0) {
            printf("| ");
        }

        for (unsigned int limb_index = 0; limb_index < num_limbs; limb_index++) {
            printf("%0*" PRI_LIMB " ", LIMB_SIZE_IN_HEX, extract_limb(num, num_limbs - limb_index - 1, entry_in_limb_index, NUM_ENTRIES_IN_LIMB));
        }
        printf("| ");
    }
    printf("\n");
}

void print_num_gmp(gmp_int_t num_gmp, unsigned int num_limbs) {
    limb_t tmp[num_limbs];
    convert_gmp_to_num(tmp, num_gmp, num_limbs);
    print_num(tmp, num_limbs);
}

void convert_gmp_to_num(limb_t *num, gmp_int_t num_gmp, unsigned int num_limbs) {
    limb_building_block_t tmp[num_limbs * NUM_ENTRIES_IN_LIMB];

    /* must clear the number, because GMP will only fill enough words that is
     * needed, so the last words of num may not be set automatically.
     */
    for (unsigned int i = 0; i < num_limbs; i++) {
        for (unsigned int j = 0; j < NUM_ENTRIES_IN_LIMB; j++) {
            tmp[(i * NUM_ENTRIES_IN_LIMB) + j] = 0;
        }
    }

    gmp_int_export(tmp, NULL, -1, LIMB_SIZE_IN_BYTES, 0, NUM_EXCESS_BASE_BITS, num_gmp, num_limbs);
    transpose_num(tmp, NUM_ENTRIES_IN_LIMB, num_limbs);

    for (unsigned int i = 0; i < num_limbs; i++) {
        for (unsigned int j = 0; j < NUM_ENTRIES_IN_LIMB; j++) {
            limb_building_block_t *src = ((limb_building_block_t *) tmp) + (i * NUM_ENTRIES_IN_LIMB) + j;
            limb_building_block_t *dst = ((limb_building_block_t *) num) + (i * NUM_ENTRIES_IN_LIMB) + j;
            *dst = *src;
        }
    }
}

void convert_num_to_gmp(gmp_int_t num_gmp, limb_t *num, unsigned int num_limbs) {
    limb_building_block_t tmp[NUM_ENTRIES_IN_LIMB][num_limbs];
    copy_num((limb_t *) tmp, num, num_limbs);
    transpose_num((limb_building_block_t *) tmp, num_limbs, NUM_ENTRIES_IN_LIMB);
    gmp_int_import(num_gmp, num_limbs, -1, LIMB_SIZE_IN_BYTES, 0, NUM_EXCESS_BASE_BITS, tmp);
}

bool is_equal_num_num(limb_t *num1, limb_t *num2, unsigned int num_limbs) {
    for (unsigned int limb_index = 0; limb_index < num_limbs; limb_index++) {
        for (unsigned int entry_in_limb_index = 0; entry_in_limb_index < NUM_ENTRIES_IN_LIMB; entry_in_limb_index++) {
            limb_building_block_t a = extract_limb(num1, limb_index, entry_in_limb_index, NUM_ENTRIES_IN_LIMB);
            limb_building_block_t b = extract_limb(num2, limb_index, entry_in_limb_index, NUM_ENTRIES_IN_LIMB);
            if (a != b) {
                return false;
            }
        }
    }
    return true;
}

bool is_equal_num_gmp(limb_t *num, gmp_int_t num_gmp, unsigned int num_limbs) {
    int res[NUM_ENTRIES_IN_LIMB];
    cmp_num_gmp(res, num, num_gmp, num_limbs);

    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        if (res[i] != 0) {
            return false;
        }
    }

    return true;
}

void cmp_num_gmp(int *res, limb_t *num, gmp_int_t num_gmp, unsigned int num_limbs) {
    gmp_int_t tmp;
    gmp_int_init(tmp);

    convert_num_to_gmp(tmp, num, num_limbs);
    gmp_int_cmp(res, num_gmp, tmp);

    gmp_int_clear(tmp);
}

void generate_random_gmp_less_than(gmp_int_t num_gmp, gmp_int_t strict_upper_bound_gmp, gmp_randstate_t gmp_random_state) {
    gmp_int_urandomm(num_gmp, gmp_random_state, strict_upper_bound_gmp);
}

void generate_random_gmp_number(gmp_int_t num_gmp, unsigned int precision_in_bits, gmp_randstate_t gmp_random_state) {
    /* random number with long chain of consecutive 0s and 1s for testing */
    gmp_int_rrandomb(num_gmp, gmp_random_state, precision_in_bits);
}

void generate_random_prime_gmp_number(gmp_int_t num_gmp, unsigned int precision_in_bits, gmp_randstate_t gmp_random_state) {
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        do {
            /* finding a random prime number with a long chain of 0s and 1s is hard,
             * so we use a more "general" random number
             */
            mpz_urandomb(num_gmp[i], gmp_random_state, precision_in_bits);
        } while (mpz_probab_prime_p(num_gmp[i], 25) == 0); /* definitely not composite */
    }
}

three_sorted_gmp get_three_sorted_gmp(unsigned int precision_in_bits, gmp_randstate_t gmp_random_state) {
    three_sorted_gmp output;
    gmp_int_init(output.big);
    gmp_int_init(output.middle);
    gmp_int_init(output.small);

    bool equalities_found = false;
    do {
        equalities_found = false;
        generate_random_gmp_number(output.big, precision_in_bits, gmp_random_state);
        generate_random_gmp_number(output.middle, precision_in_bits, gmp_random_state);
        generate_random_gmp_number(output.small, precision_in_bits, gmp_random_state);

        for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
            equalities_found |= ((mpz_cmp(output.big[i], output.middle[i]) == 0) ||
                                 (mpz_cmp(output.big[i], output.small[i]) == 0)  ||
                                 (mpz_cmp(output.middle[i], output.small[i]) == 0));
        }
    } while (equalities_found);

    /* How to sort 3 values in descending order (a > b > c)
     *  if (a > b) swap(a, b);
     *  if (a > c) swap(a, c);
     *  if (b > c) swap(b, c);
     */
    for (unsigned int i = 0; i < NUM_ENTRIES_IN_LIMB; i++) {
        if (mpz_cmp(output.small[i], output.middle[i]) == 1) mpz_swap(output.small[i], output.middle[i]);
        if (mpz_cmp(output.small[i], output.big[i]) == 1) mpz_swap(output.small[i], output.big[i]);
        if (mpz_cmp(output.middle[i], output.big[i]) == 1) mpz_swap(output.middle[i], output.big[i]);
    }

    return output;
}

void clear_three_sorted_gmp(three_sorted_gmp x) {
    gmp_int_clear(x.big);
    gmp_int_clear(x.middle);
    gmp_int_clear(x.small);
}

void copy_num(limb_t *b, limb_t *a, unsigned int num_limbs) {
    for (unsigned int i = 0; i < num_limbs; i++) {
        store_limb(b, i, load_limb(a, i));
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

bool equals_num_limb(limb_building_block_t *num, limb_building_block_t value, unsigned int num_limbs) {
    for (unsigned int i = 1; i < num_limbs; i++) {
        if (num[i] != 0) {
            return false;
        }
    }

    return num[0] == value;
}

void set_num_limb(limb_building_block_t *num, limb_building_block_t value, unsigned int num_limbs) {
    for (unsigned int i = 1; i < num_limbs; i++) {
        num[i] = 0;
    }
    num[0] = value;
}

bool is_even(limb_building_block_t *num) {
    return (num[0] & 1) == 0;
}


