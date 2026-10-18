#include <iostream>
#include <chrono>

#include "debug/print.hpp"
#include "frontend/lexer/tokens.hpp"
#include "frontend/astgen/astgen.hpp"
#include "backend/codegen/codegen.hpp"

int main() {
    auto lexstart = std::chrono::high_resolution_clock::now();
    
    auto tokens = tokenize("var name = 'a'"); // We only measure how it took to tokenize, not to show the tokens

    auto lexend = std::chrono::high_resolution_clock::now();
    
    show(tokens);

    auto lextime = std::chrono::duration_cast<std::chrono::nanoseconds>(lexend - lexstart).count();

    std::cout << "Lexing time: " << lextime << " nanosecons." << std::endl;
    std::cout << "Or: " << lextime / 1000000.0 << " ms." << std::endl;

    auto astart = std::chrono::high_resolution_clock::now();
    auto ast = createAST(tokens);

    auto astend = std::chrono::high_resolution_clock::now();
    auto asttime = std::chrono::duration_cast<std::chrono::nanoseconds>(astend - astart).count();

    std::cout << "ASTgen time: " << asttime << " nanosecons." << std::endl;
    std::cout << "Or: " << asttime / 1000000.0 << " ms." << std::endl;  

    show(ast);

    auto genstart = std::chrono::high_resolution_clock::now();
    generateBytecode(ast);

    auto genend = std::chrono::high_resolution_clock::now();
    auto gentime = std::chrono::duration_cast<std::chrono::nanoseconds>(genend - genstart).count();

    std::cout << "Codegen time: " << gentime << " nanosecons." << std::endl;
    std::cout << "Or: " << gentime / 1000000.0 << " ms." << std::endl;  




    return 0;
}
