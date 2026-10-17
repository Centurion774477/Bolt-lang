#if defined(_MSC_VER) && !defined(__clang__)
#define BOLT_UNREACHABLE() __assume(0)
#elif defined(__GNUC__) || defined(__clang__)
#define BOLT_UNREACHABLE() __builtin_unreachable()
#else
#define BOLT_UNREACHABLE() do {} while (true)
#endif

#include <stdint.h>
#include <stdio.h>

int execute(const uint8_t* src) {
    uint8_t byte = *src;
    switch (byte) {
        case 0:
            printf("Hi");
        case 255:
            return 0;
        default:
            BOLT_UNREACHABLE();
    }
    return 0;
}