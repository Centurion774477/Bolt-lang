#include "../common/bytecode.h"
#include "executor.h"
#include <stdint.h>

int main() {
    uint8_t operations[2];
    operations[0] = 0;
    operations[1] = 255;

    return execute(operations);
}