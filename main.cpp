#include <iostream>
#include <chrono>

#include "debug/print.hpp"
#include "frontend/lexer/tokens.hpp"
#include "frontend/astgen/astgen.hpp"

int main() {
    auto lexstart = std::chrono::high_resolution_clock::now();
    
    auto tokens = tokenize("var name = 'a'"); // We only measure how it took to tokenize, not to show the tokens

    auto lexend = std::chrono::high_resolution_clock::now();
    
    show(tokens);

    auto lextime = std::chrono::duration_cast<std::chrono::nanoseconds>(lexend - lexstart).count();

    std::cout << "Lexing time: " << lextime << " nanosegons." << std::endl;
    std::cout << "Or: " << lextime / 1000000.0 << " ms." << std::endl;

    auto astart = std::chrono::high_resolution_clock::now();
    auto ast = createAST(tokens);

    auto astend = std::chrono::high_resolution_clock::now();
    auto asttime = std::chrono::duration_cast<std::chrono::nanoseconds>(astend - astart).count();

    std::cout << "ASTgen time: " << asttime << " nanosegons." << std::endl;
    std::cout << "Or: " << asttime / 1000000.0 << " ms." << std::endl;  

    show(ast);



    return 0;
}
