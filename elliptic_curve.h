#ifndef ELLIPTIC_CURVE_H_
#define ELLIPTIC_CURVE_H_

    #include "constants.h"
    #include "limb.h"
    #include "gmp_int.h"

    struct curve_point {
        limb_t x[NUM_LIMBS];
        limb_t y[NUM_LIMBS];
    };

    struct curve_point_gmp {
        gmp_int_t x;
        gmp_int_t y;
    };

    struct curve_point add_point_point(struct curve_point p1, struct curve_point p2);
    struct curve_point_gmp add_point_point_gmp(struct curve_point_gmp p1, struct curve_point_gmp p2);
    bool is_on_curve_num(limb_t *x_num, limb_t *y_num);
    bool is_on_curve_point(struct curve_point p);
    bool is_on_curve_gmp(gmp_int_t x_gmp, gmp_int_t y_gmp);

#endif /* ELLIPTIC_CURVE_H_ */
