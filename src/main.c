#include <stdio.h>
#include <stdlib.h>

#include "math_utils.h"

static int verbose = 0;

static void print_usage(const char* program)
{
    printf("usage: %s <a> <b>\n", program);
    printf("example: %s 3 4\n", program);
}

static int parse_number(const char* text, int* out)
{
    char* end = NULL;
    long value = strtol(text, &end, 10);

    if (end == text || *end != '\0') {
        return 0;
    }

    *out = (int)value;
    return 1;
}

int main(int argc, char** argv)
{
    int a, b;

    if (argc != 3) {
        print_usage(argv[0]);
        return 1;
    }

    if (!parse_number(argv[1], &a) || !parse_number(argv[2], &b)) {
        fprintf(stderr, "error: arguments must be integers\n");
        return 1;
    }

    if (verbose) {
        printf("a = %d, b = %d\n", a, b);
    }

    printf("sum = %d\n", add(a, b));
    printf("diff = %d\n", subtract(a, b));
    printf("a * 2 = %d\n", multiply_by_two(a));

    if (is_even(a)) {
        printf("a is even\n");
    } else {
        printf("a is odd\n");
    }

    return 0;
}
