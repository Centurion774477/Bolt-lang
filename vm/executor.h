#pragma once
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../common/bytecode.h"

static inline int read_int(const uint8_t** ip) {
    uint8_t v = **ip;
    (*ip)++;
    return (int)v;
}

void execute(DynamicStack* restrict s, const uint8_t* restrict code);