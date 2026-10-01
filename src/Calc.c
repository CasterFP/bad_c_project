#include "Calc.h"

int calc_sum(int a, int b)
{
    int result = a + b;
    return result;
}

int calc_diff(int a, int b)
{
    return a - b;
}

int calc_double(int value)
{
    return value * 2;
}

int calc_is_even(int value)
{
    if (value % 2 != 0) {
        return 0;
    }
    return 1;
}
