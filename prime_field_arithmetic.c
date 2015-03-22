#include <stdint.h>
#include <stdbool.h>
#include "constants.h"
#include "utilities.h"

unsigned int add(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const carry_in) {
	// we need to temporarily store the output of each operation, because it is possible that c is the same array as a.
	uint64_t c_tmp;
	unsigned int carry_out;

    c_tmp = a[0] + b[0] + carry_in;
    carry_out = (c_tmp < a[0]);
    c[0] = c_tmp;

    for (unsigned int i = 1; i < NUM_LIMBS; i++) {
        c_tmp = a[i] + b[i] + carry_out;
        carry_out = (c_tmp < a[i]);
        c[i] = c_tmp;
    }

    return carry_out;
}

unsigned int sub(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const borrow_in) {
	uint64_t c_tmp;
	unsigned int borrow_out;

    c_tmp = a[0] - b[0] - borrow_in;
    borrow_out = (c_tmp > a[0]);
    c[0] = c_tmp;

    for (unsigned int i = 1; i < NUM_LIMBS; i++) {
        c_tmp = a[i] - b[i] - borrow_out;
        borrow_out = (c_tmp > a[i]);
        c[i] = c_tmp;
    }

    return borrow_out;
}

bool equals_zero(uint64_t const * const num) {
	for (unsigned int i = 0; i < NUM_LIMBS; i++) {
		if (num[i] != 0) {
			return false;
		}
	}
	return true;
}

// returns -1 if a < b
// returns  0 if a == b
// returns +1 if a > b
int cmp(uint64_t const * const a, uint64_t const * const b) {
	uint64_t tmp[NUM_LIMBS];
	unsigned int borrow_out = sub(tmp, a, b, 0);

	if (borrow_out) {
		return -1;
	} else if (equals_zero(tmp)) {
		return 0;
	} else {
		return 1;
	}
}

void add_mod(uint64_t * const c, uint64_t * const a, uint64_t * const b, uint64_t * const m) {
	add(c, a, b, 0);
	if (cmp(c, m) >= 0) {
		sub(c, c, m, 0);
	}
}

void sub_mod(uint64_t * const c, uint64_t * const a, uint64_t * const b, uint64_t * const m) {
	unsigned int borrow_out = sub(c, a, b, 0);
	if (borrow_out) {
		add(c, c, m, 0);
	}
}
