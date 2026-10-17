#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "executor.h"

int main(void) {
    FILE* file = fopen("main.bvm", "rb");
    if (!file) {
        fprintf(stderr, "BVM File Error: Could't open 'main.bvm'\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    if (file_size <= 0) {
        fprintf(stderr, "BVM File Error: Blank or unvalid file\n");
        fclose(file);
        return 1;
    }

    uint8_t* bytecode = (uint8_t*)malloc(file_size);
    if (!bytecode) {
        fprintf(stderr, "BVM Memory Error: Missing space for loading bytecode\n");
        fclose(file);
        return 1;
    }

    size_t bytes_read = fread(bytecode, 1, file_size, file);
    fclose(file);

    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "BVM File Error: couln't read file content\n");
        free(bytecode);
        return 1;
    }

    DynamicStack stack;
    init_stack(&stack, 64);

    execute(&stack, bytecode);
    int result = peek(&stack);

    free_stack(&stack);
    free(bytecode);

    return result;
}
