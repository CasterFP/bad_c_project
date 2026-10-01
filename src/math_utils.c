#include "math_utils.h"

// TODO: переписать на uint64_t, тут везде int

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply_by_two(int value)
{
    return value * 2;
}

int is_even(int value)
{
    if (value % 2 == 0) {
        return 1;
    }

    return 0;
}
