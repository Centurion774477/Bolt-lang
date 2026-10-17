#include <iostream>
#include <vector>
#include <string>
#include "../frontend/lexer/tokens.hpp"
#include "print.hpp"

#include <array>
#include <string_view>

std::string_view tokenToString(tokens type) {
    static constexpr std::array<std::string_view, 9> token_names = {
        "var",          // 0
        "c_int",        // 1
        "plus",         // 2
        "minus",        // 3
        "star",         // 4
        "slash",        // 5
        "c_str",        // 6
        "identifier",   // 7
        "equal"         // 8
    };

    auto index = static_cast<size_t>(type);
    
    if (index < token_names.size()) {
        return token_names[index];
    }
    return "invalid";
}


void show(std::vector<Token> vec) {
    std::cout << "> TOKENS:\n";
    for (Token t : vec) {
        std::cout << "    " << tokenToString(t.type) << "[" << t.value << "]\n";
    }
    std::cout << "< END TOKENS; \n";
}