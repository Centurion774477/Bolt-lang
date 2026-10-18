#include "../../frontend/astgen/astgen.hpp"
#include "../../frontend/lexer/tokens.hpp"
#include "../../common/bytecode.h"

#include <string>
#include <fstream>
#include <cstdint>
#include <vector>
#include <variant>
#include <iostream>
#include <type_traits>

namespace {
    void emit_u8(std::vector<uint8_t>& out, uint8_t v) {
        out.push_back(v);
    }

    void emit_u32(std::vector<uint8_t>& out, uint32_t v) {
        out.push_back(static_cast<uint8_t>((v >> 0) & 0xFF));
        out.push_back(static_cast<uint8_t>((v >> 8) & 0xFF));
        out.push_back(static_cast<uint8_t>((v >> 16) & 0xFF));
        out.push_back(static_cast<uint8_t>((v >> 24) & 0xFF));
    }
}

int generateBytecode(const AST& ast, const std::string& path) {
    std::vector<uint8_t> bytecode;
    bytecode.reserve(ast.nodes.size() * 8);

    for (const auto& node : ast.nodes) {
        std::visit([&](const auto& value) {
            using T = std::decay_t<decltype(value)>;

            if constexpr (std::is_same_v<T, VarDecl>) {
                emit_u8(bytecode, 0x09);
                emit_u32(bytecode, static_cast<uint32_t>(value.name_index));
                emit_u8(bytecode, 0x00);
                emit_u8(bytecode, 0x01);
                emit_u32(bytecode, static_cast<uint32_t>(value.initializer));
            } else if constexpr (std::is_same_v<T, Literal>) {
                emit_u8(bytecode, 0x10);
                emit_u32(bytecode, static_cast<uint32_t>(value.value));
            }
        }, node.data);
    }

    std::ofstream output(path, std::ios::binary);
    if (!output) {
        std::cerr << "Bolt File Error: couldn't open output file.\n";
        return 1;
    }

    output.write(reinterpret_cast<const char*>(bytecode.data()),
                 static_cast<std::streamsize>(bytecode.size()));
    output.close();

    std::cout << "Bytecode written successfully.\n";
    return 0;
}