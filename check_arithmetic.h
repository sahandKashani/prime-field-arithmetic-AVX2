#ifndef CHECK_ARITHMETIC_H_
#define CHECK_ARITHMETIC_H_

#include <stdbool.h>

#define NUMBER_OF_TESTS (1 << 10)
#define SEED (12345)

bool test_add_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_add_num_limb(unsigned int number_of_tests, unsigned int seed);
bool test_sub_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_mul_limb_limb(unsigned int number_of_tests, unsigned int seed);
bool test_mul_num_limb(unsigned int number_of_tests, unsigned int seed);
bool test_mul_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_add_mod_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_sub_mod_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_mul_montgomery_num_num(unsigned int number_of_tests, unsigned int seed);
bool test_point_addition(unsigned int number_of_tests);
bool test_point_double(unsigned int number_of_tests);
bool test_point_neg(unsigned int number_of_tests);
void check_add_num_num(unsigned int number_of_tests, unsigned int seed);
void check_add_num_limb(unsigned int number_of_tests, unsigned int seed);
void check_sub_num_num(unsigned int number_of_tests, unsigned int seed);
void check_mul_limb_limb(unsigned int number_of_tests, unsigned int seed);
void check_mul_num_limb(unsigned int number_of_tests, unsigned int seed);
void check_mul_num_num(unsigned int number_of_tests, unsigned int seed);
void check_add_mod_num_num(unsigned int number_of_tests, unsigned int seed);
void check_sub_mod_num_num(unsigned int number_of_tests, unsigned int seed);
void check_mul_montgomery_num_num(unsigned int number_of_tests, unsigned int seed);
void check_add_point_point(unsigned int number_of_tests);
void check_double_point(unsigned int number_of_tests);
void check_neg_point(unsigned int number_of_tests);

#endif /* CHECK_ARITHMETIC_H_ */
