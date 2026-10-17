#include "frontend/lexer/tokens.hpp"
#include <iostream>
#include "debug/print.hpp"


int main() {
    show(tokenize("var name = 'a'"));
    return 0;
}