#ifndef ELLIPTIC_CURVE_H_
#define ELLIPTIC_CURVE_H_

    #include "constants.h"
    #include "limb.h"
    #include "gmp_int.h"

    struct curve_point {
        limb_t x[NUM_LIMBS];
        limb_t y[NUM_LIMBS];
    };

    struct curve_point add_point_point(struct curve_point a, struct curve_point b, limb_t *m, limb_t m_prime);
    bool is_on_curve_gmp(gmp_int_t x_gmp, gmp_int_t y_gmp);

#endif /* ELLIPTIC_CURVE_H_ */
