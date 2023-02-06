#include "asm_ops.h"
#include <stdint.h>

uint64_t cmp_less(uint64_t a, uint64_t b) { return a < b; };

uint64_t cmp_great(uint64_t a, uint64_t b) { return a > b; };

uint64_t cmp_eq(uint64_t a, uint64_t b) { return a == b; };

uint64_t cmp_neq(uint64_t a, uint64_t b) { return a != b; };

uint64_t cmp_leq(uint64_t a, uint64_t b) { return a <= b; };

uint64_t cmp_geq(uint64_t a, uint64_t b) { return a >= b; };

