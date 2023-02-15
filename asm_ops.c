#include "asm_ops.h"
#include <stdint.h>

int64_t cmp_less(int64_t a, int64_t b) { return a < b; };

int64_t cmp_great(int64_t a, int64_t b) { return a > b; };

int64_t cmp_eq(int64_t a, int64_t b) { return a == b; };

int64_t cmp_neq(int64_t a, int64_t b) { return a != b; };

int64_t cmp_leq(int64_t a, int64_t b) { return a <= b; };

int64_t cmp_geq(int64_t a, int64_t b) { return a >= b; };
