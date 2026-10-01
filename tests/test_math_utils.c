/*
 *  Юнит-тесты для math_utils.
 *
 *  Требования к тестам, которые нам на занятиях говорили:
 *    - должны быть быстрыми: тут нет ни файлов, ни сети, ни вывода в консоль
 *    - должны покрывать разные случаи, особенно краевые (0, отрицательные,
 *      INT_MAX / 2, INT_MIN / 2, INT_MIN)
 *    - их должно быть много, иначе рефакторинг ломает всё молча
 *    - запускаются при каждом изменении кода
 *    - имена тестов и есть документация: их видно в выводе ctest и в CI
 *
 *  Чего тут нет: INT_MAX * 2 или a + INT_MAX. Это UB, такие проверки не пишем.
 */
#include <limits.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include <cmocka.h>

#include "math_utils.h"

/* ------------------------------------------------------------------ add */

static void test_add_of_positive_numbers(void** state)
{
    (void)state;
    assert_int_equal(add(2, 3), 5);
}

static void test_add_of_negative_numbers(void** state)
{
    (void)state;
    assert_int_equal(add(-2, -3), -5);
}

static void test_add_of_zero_is_neutral(void** state)
{
    (void)state;
    assert_int_equal(add(5, 0), 5);
    assert_int_equal(add(0, 5), 5);
    assert_int_equal(add(0, -5), -5);
}

static void test_add_is_commutative(void** state)
{
    int a = -17;
    int b = 42;
    (void)state;

    assert_int_equal(add(a, b), add(b, a));
}

static void test_add_near_int_max(void** state)
{
    (void)state;
    assert_int_equal(add(INT_MAX / 2, INT_MAX / 2), 2 * (INT_MAX / 2));
}

/* ------------------------------------------------------------ subtract */

static void test_subtract_of_positive_numbers(void** state)
{
    (void)state;
    assert_int_equal(subtract(7, 3), 4);
}

static void test_subtract_of_equal_numbers_is_zero(void** state)
{
    (void)state;
    assert_int_equal(subtract(5, 5), 0);
}

static void test_subtract_of_negative_numbers(void** state)
{
    (void)state;
    assert_int_equal(subtract(-3, -8), 5);
}

static void test_subtract_undoes_add(void** state)
{
    (void)state;
    assert_int_equal(add(subtract(10, 4), 4), 10);
}

/* -------------------------------------------------------------- is_even */

static void test_is_even_of_zero(void** state)
{
    (void)state;
    assert_int_equal(is_even(0), 1);
}

static void test_is_even_of_positive_even(void** state)
{
    (void)state;
    assert_int_equal(is_even(4), 1);
    assert_int_equal(is_even(100), 1);
}

static void test_is_even_of_positive_odd(void** state)
{
    (void)state;
    assert_int_equal(is_even(7), 0);
}

static void test_is_even_of_negative_even(void** state)
{
    (void)state;
    assert_int_equal(is_even(-4), 1);
}

static void test_is_even_of_negative_odd(void** state)
{
    (void)state;
    assert_int_equal(is_even(-7), 0);
}

static void test_is_even_of_int_min(void** state)
{
    (void)state;
    assert_int_equal(is_even(INT_MIN), 1);
}

/* ------------------------------------------------------- multiply_by_two */

static void test_multiply_by_two_of_zero_is_zero(void** state)
{
    (void)state;
    assert_int_equal(multiply_by_two(0), 0);
}

static void test_multiply_by_two_of_one_is_two(void** state)
{
    (void)state;
    assert_int_equal(multiply_by_two(1), 2);
}

static void test_multiply_by_two_of_two_is_four(void** state)
{
    (void)state;
    assert_int_equal(multiply_by_two(2), 4);
}

static void test_multiply_by_two_of_ten_is_twenty(void** state)
{
    (void)state;
    assert_int_equal(multiply_by_two(10), 20);
}

static void test_multiply_by_two_of_negative_three(void** state)
{
    (void)state;
    assert_int_equal(multiply_by_two(-3), -6);
}

static void test_multiply_by_two_of_negative_one_stays_negative(void** state)
{
    (void)state;
    assert_true(multiply_by_two(-1) < 0);
}

static void test_multiply_by_two_near_int_max(void** state)
{
    (void)state;
    assert_int_equal(multiply_by_two(INT_MAX / 2), 2 * (INT_MAX / 2));
}

static void test_multiply_by_two_near_int_min(void** state)
{
    (void)state;
    assert_int_equal(multiply_by_two(INT_MIN / 2), 2 * (INT_MIN / 2));
}

static void test_multiply_by_two_applied_twice_doubles_again(void** state)
{
    (void)state;
    assert_int_equal(multiply_by_two(multiply_by_two(5)), 20);
}

/* ------------------------------------------------------------------ *
 *  Список тестов. Одно имя - один тест, и один запуск ctest.          *
 * ------------------------------------------------------------------ */

#define MATH_UTILS_TESTS(X)                                \
    X(test_add_of_positive_numbers)                        \
    X(test_add_of_negative_numbers)                        \
    X(test_add_of_zero_is_neutral)                         \
    X(test_add_is_commutative)                             \
    X(test_add_near_int_max)                               \
    X(test_subtract_of_positive_numbers)                   \
    X(test_subtract_of_equal_numbers_is_zero)              \
    X(test_subtract_of_negative_numbers)                   \
    X(test_subtract_undoes_add)                            \
    X(test_is_even_of_zero)                                \
    X(test_is_even_of_positive_even)                       \
    X(test_is_even_of_positive_odd)                        \
    X(test_is_even_of_negative_even)                       \
    X(test_is_even_of_negative_odd)                        \
    X(test_is_even_of_int_min)                             \
    X(test_multiply_by_two_of_zero_is_zero)                \
    X(test_multiply_by_two_of_one_is_two)                  \
    X(test_multiply_by_two_of_two_is_four)                 \
    X(test_multiply_by_two_of_ten_is_twenty)               \
    X(test_multiply_by_two_of_negative_three)              \
    X(test_multiply_by_two_of_negative_one_stays_negative) \
    X(test_multiply_by_two_near_int_max)                   \
    X(test_multiply_by_two_near_int_min)                   \
    X(test_multiply_by_two_applied_twice_doubles_again)

/* группа из одного теста, для запуска по имени */
#define DEFINE_TEST_GROUP(fn) \
    static const struct CMUnitTest fn##_group[] = { cmocka_unit_test(fn) };

MATH_UTILS_TESTS(DEFINE_TEST_GROUP)

#undef DEFINE_TEST_GROUP

/* все тесты разом */
#define ADD_TO_ALL_TESTS(fn) cmocka_unit_test(fn),
static const struct CMUnitTest all_tests[] = {
    MATH_UTILS_TESTS(ADD_TO_ALL_TESTS)
};
#undef ADD_TO_ALL_TESTS

int main(int argc, char** argv)
{
    if (argc > 1) {
#define RUN_TEST_IF_NAME_MATCHES(fn)                           \
    if (strcmp(argv[1], #fn) == 0) {                           \
        return cmocka_run_group_tests(fn##_group, NULL, NULL); \
    }

        MATH_UTILS_TESTS(RUN_TEST_IF_NAME_MATCHES)

#undef RUN_TEST_IF_NAME_MATCHES

        fprintf(stderr, "unknown test: %s\n", argv[1]);
        return 2;
    }

    return cmocka_run_group_tests(all_tests, NULL, NULL);
}
