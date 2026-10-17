#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    OP_PUSH,
    OP_POP,
    OP_ADD,
    OP_HALT,
    OP_COUNT   // keep last: number of opcodes
} Operations;

#ifdef __cplusplus
}
#endif