#include "../../frontend/astgen/astgen.hpp"
#include "../../frontend/lexer/tokens.hpp"
#include "../../common/bytecode.h"

#include <string>
#include <fstream>
#include <cstdint>
#include <vector>
#include <variant>
#include <iostream>

int generateBytecode(AST ast) {
    std::vector<uint8_t> bytecode;
    std::ofstream output("main.bvm", std::ios::out | std::ios::binary);

    if (!output.is_open()) {
        std::cerr << "Bolt File Error: couldn't open output file.\n";
        return 1;
    }

    size_t current = 0;
    while (current < ast.nodes.size()) {
        if (auto vardecl = std::get_if<VarDecl>(&(ast.nodes[current].data))) {
            bytecode.push_back(0x09); // identifier
            bytecode.push_back(static_cast<uint8_t>(vardecl->name_index));
            bytecode.push_back(0x00);
            bytecode.push_back(0x01); // separator: name 0x00 0x01 value
            bytecode.push_back(static_cast<uint8_t>(vardecl->initializer));
        } else if (auto literal = std::get_if<Literal>(&(ast.nodes[current].data))) {
            bytecode.push_back(0x10); // Identifier
            bytecode.push_back(static_cast<uint8_t>(literal->value)); 
        }
        current++;
    }

    output.write(reinterpret_cast<const char*>(bytecode.data()), bytecode.size());
    output.close();
    
    std::cout << "Bytecode written successfully.\n";
    return 0;
}
