#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "constants.h"
#include "utilities.h"
#include "prime_field_arithmetic.h"

unsigned int add(uint64_t *c, uint64_t const *a, uint64_t const *b, unsigned int const num_limbs, unsigned int const carry_in) {
	// we need to temporarily store the output of each operation, because it is
	// possible that c is the same array as a.
	uint64_t c_tmp;
	unsigned int carry_out;

    c_tmp = a[0] + b[0] + carry_in;
    carry_out = (c_tmp < a[0]);
    c[0] = c_tmp;

    for (unsigned int i = 1; i < num_limbs; i++) {
        c_tmp = a[i] + b[i] + carry_out;
        carry_out = (c_tmp < a[i]);
        c[i] = c_tmp;
    }

    return carry_out;
}

unsigned int sub(uint64_t *c, uint64_t const *a, uint64_t const *b, unsigned int const num_limbs, unsigned int const borrow_in) {
	uint64_t c_tmp;
	unsigned int borrow_out;

    c_tmp = a[0] - b[0] - borrow_in;
    borrow_out = (c_tmp > a[0]);
    c[0] = c_tmp;

    for (unsigned int i = 1; i < num_limbs; i++) {
        c_tmp = a[i] - b[i] - borrow_out;
        borrow_out = (c_tmp > a[i]);
        c[i] = c_tmp;
    }

    return borrow_out;
}

void mul(uint64_t *c, uint64_t const *a, uint64_t const *b, unsigned int const num_limbs) {
	clear_num(c, num_limbs);

	uint64_t op1 = a[0];
	uint64_t op2 = b[0];

	for (unsigned int i = 0; i < num_limbs; i++) {
		for (unsigned int j = 0; j < num_limbs; j++) {

		}
	}
}

bool equals_zero(uint64_t const *num, unsigned int const num_limbs) {
	for (unsigned int i = 0; i < num_limbs; i++) {
		if (num[i] != 0) {
			return false;
		}
	}
	return true;
}

// returns -1 if a < b
// returns  0 if a == b
// returns +1 if a > b
int cmp(uint64_t const *a, uint64_t const *b, unsigned int const num_limbs) {
	uint64_t *tmp = calloc(num_limbs, sizeof(uint64_t));
	assert(tmp != NULL);
	unsigned int borrow_out = sub(tmp, a, b, num_limbs, 0);

	if (borrow_out) {
		free(tmp);
		return -1;
	} else if (equals_zero(tmp, num_limbs)) {
		free(tmp);
		return 0;
	} else {
		free(tmp);
		return 1;
	}
}

void add_mod(uint64_t *c, uint64_t const *a, uint64_t const *b, uint64_t const *m, unsigned int const num_limbs) {
	add(c, a, b, num_limbs, 0);
	if (cmp(c, m, num_limbs) >= 0) {
		sub(c, c, m, num_limbs, 0);
	}
}

void sub_mod(uint64_t *c, uint64_t const *a, uint64_t const *b, uint64_t const *m, unsigned int const num_limbs) {
	unsigned int borrow_out = sub(c, a, b, num_limbs, 0);
	if (borrow_out) {
		add(c, c, m, num_limbs, 0);
	}
}
