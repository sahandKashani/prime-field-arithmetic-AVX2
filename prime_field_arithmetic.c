#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "constants.h"
#include "utilities.h"
#include "prime_field_arithmetic.h"

unsigned int add(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs, unsigned int const carry_in) {
	unsigned int carry_out = carry_in;

    for (unsigned int i = 0; i < num_limbs; i++) {
		// we need to temporarily store the output of each operation, because it is
		// possible that c is the same array as a or b.
		uint64_t c_tmp = 0;

        c_tmp = a[i] + carry_out;
        carry_out = (c_tmp < a[i]);
        c_tmp += b[i];
        carry_out |= (c_tmp < b[i]);
        c[i] = c_tmp;
    }

    return carry_out;
}

unsigned int add_num_64(uint64_t * const c, uint64_t const * const a, uint64_t const b, unsigned int const num_limbs, unsigned int const carry_in) {
	// we need to temporarily store the output of each operation, because it is
	// possible that c is the same array as a.
	uint64_t c_tmp = 0;
	unsigned int carry_out = 0;

    c_tmp = a[0] + carry_in;
    carry_out = (c_tmp < a[0]);
    c_tmp += b;
    carry_out |= (c_tmp < b);
    c[0] = c_tmp;

    for (unsigned int i = 1; i < num_limbs; i++) {
        c_tmp = a[i] + carry_out;
        carry_out = (c_tmp < a[i]);
        c[i] = c_tmp;
    }

    return carry_out;
}

unsigned int sub(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs, unsigned int const borrow_in) {
	unsigned int borrow_out = borrow_in;

    for (unsigned int i = 0; i < num_limbs; i++) {
		// we need to temporarily store the output of each operation, because it is
		// possible that c is the same array as a or b.
		uint64_t c_tmp = 0;
		uint64_t c_tmp_old = 0;

        c_tmp = a[i] - borrow_out;
        c_tmp_old = c_tmp;
        borrow_out = (c_tmp > a[i]);
        c_tmp -= b[i];
        borrow_out |= (c_tmp > c_tmp_old);
        c[i] = c_tmp;
    }

    return borrow_out;
}

void mul64_to_128(uint64_t * const c_hi, uint64_t * const c_lo, uint64_t const a, uint64_t const b) {
	uint32_t a_32[2] = {a & 0xffffffff, (uint32_t) (a >> 32)};
	uint32_t b_32[2] = {b & 0xffffffff, (uint32_t) (b >> 32)};
	uint32_t c_32[4] = {0, 0, 0, 0};

	uint64_t inner_product = 0;
	uint32_t inner_product_lo = 0;
	uint32_t inner_product_hi = 0;

	for (unsigned int i = 0; i < 2; i++) {
		inner_product_hi = 0;
		for (unsigned int j = 0; j < 2; j++) {
			inner_product = c_32[i + j] + (((uint64_t) a_32[i]) * b_32[j]) + inner_product_hi;
			inner_product_lo = inner_product & (0xffffffff);
			inner_product_hi = (uint32_t) (inner_product >> 32);
			c_32[i + j] = inner_product_lo;
		}
		c_32[i + 2] = inner_product_hi;
	}

	*c_lo = (((uint64_t) c_32[1]) << 32) + c_32[0];
	*c_hi = (((uint64_t) c_32[3]) << 32) + c_32[2];
}

void mul_num_64(uint64_t * const c, uint64_t const * const a, uint64_t const b, unsigned int const num_limbs) {
	uint64_t res[num_limbs + 1];
	clear_num(res, num_limbs + 1);

	uint64_t inner_product[2] = {0, 0};
	unsigned int carry_out = 0;
	for (unsigned int i = 0; i < num_limbs; i++) {
		mul64_to_128(&inner_product[1], &inner_product[0], a[i], b);
		carry_out = add(res + i, res + i, inner_product, 2, carry_out);
	}

	copy_num(c, res, num_limbs + 1);
}

void mul(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs) {
	uint64_t res[2 * num_limbs];
	clear_num(res, 2 * num_limbs);

	for (unsigned int i = 0; i < num_limbs; i++) {
		uint64_t tmp[num_limbs + 1];
		mul_num_64(tmp, a, b[i], num_limbs);
		add(res + i, res + i, tmp, num_limbs + 1, 0);
	}

	copy_num(c, res, 2 * num_limbs);
}

bool equals_zero(uint64_t const * const num, unsigned int const num_limbs) {
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
int cmp(uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs) {
	uint64_t tmp[num_limbs];
	unsigned int borrow_out = sub(tmp, a, b, num_limbs, 0);

	if (borrow_out) {
		return -1;
	} else if (equals_zero(tmp, num_limbs)) {
		return 0;
	} else {
		return 1;
	}
}

void and(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, unsigned int const num_limbs) {
	for (unsigned int i = 0; i < num_limbs; i++) {
		c[i] = a[i] & b[i];
	}
}

void add_mod(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, uint64_t const * const m, unsigned int const num_limbs) {
#ifdef BRANCHLESS_MODULAR_ADDITION
	uint64_t mask[num_limbs];
	clear_num(mask, num_limbs);

	add(c, a, b, num_limbs, 0);
	unsigned int borrow_out = sub(c, c, m, num_limbs, 0);
	sub(mask, mask, mask, num_limbs, borrow_out);
	and(mask, m, mask, num_limbs);
	add(c, c, mask, num_limbs, 0);
#else
	add(c, a, b, num_limbs, 0);
	if (cmp(c, m, num_limbs) >= 0) {
		sub(c, c, m, num_limbs, 0);
	}
#endif
}

void sub_mod(uint64_t * const c, uint64_t const * const a, uint64_t const * const b, uint64_t const * const m, unsigned int const num_limbs) {
#ifdef BRANCHLESS_MODULAR_SUBTRACTION
	uint64_t mask[num_limbs];
	clear_num(mask, num_limbs);

	unsigned int borrow_out = sub(c, a, b, num_limbs, 0);
	sub(mask, mask, mask, num_limbs, borrow_out);
	and(mask, m, mask, num_limbs);
	add(c, c, mask, num_limbs, 0);
#else
	unsigned int borrow_out = sub(c, a, b, num_limbs, 0);
	if (borrow_out) {
		add(c, c, m, num_limbs, 0);
	}
#endif
}

void mul_montgomery(uint64_t * const z, uint64_t const * const x, uint64_t const * const y, uint64_t const * const m, uint64_t m_prime, unsigned int const num_limbs) {
	uint64_t A[num_limbs + 1];
	clear_num(A, num_limbs + 1);

	for (unsigned int i = 0; i < num_limbs; i++) {
		// u_i = (a_0 + (x_i * y_0)) * m' mod b
		uint64_t ui = (A[0] + x[i] * y[0]) * m_prime;

		// A = (A + (x_i * y) + (u_i * m)) / b

		// x_i * y
		uint64_t xi_y[num_limbs + 1];
		mul_num_64(xi_y, y, x[i], num_limbs);

		// u_i * m
		uint64_t ui_m[num_limbs + 1];
		mul_num_64(ui_m, m, ui, num_limbs);

		// A = A + (x_i * y)
		add(A, A, xi_y, num_limbs + 1, 0);

		// A = A + (x_i * y) + (u_i * m)
		add(A, A, ui_m, num_limbs + 1, 0);

		// A = (A + (x_i * y) + (u_i * m)) / b
		for (unsigned int j = 0; j < num_limbs; j++) {
			A[j] = A[j + 1];
		}
		A[num_limbs] = 0;
	}

	// A[num_limbs] = 0, so it is like if A and m have the same number of limbs.
	if (cmp(A, m, num_limbs) >= 0) {
		sub(A, A, m, num_limbs, 0);
	}

	copy_num(z, A, num_limbs);
}

///*
// * (2^n - 1)*(2^n - 1) + (2^n - 1) < (2^(2*n) - 1) for all n > 0
// */
//void montgomery_reduction() {
//
//}
