#include <stdexcept>
#include <vector>
#include <iostream>

#include "../lexer/tokens.hpp"
#include "astgen.hpp"

NodeId parse_expression(ParserState& state, AST& ast) {
    Token current = state.peek();

    if (current.type == tokens::c_int) {
        Literal lit{std::stoi(current.value)};
        return ast.add_node(Node{lit});
    } else if (current.type == tokens::c_char) {
        Literal lit{(int)(current.value[0])};
        return ast.add_node(Node{lit});
    }
    throw std::runtime_error("Bolt Syntax Error: unrecognized operation");
}

AST createAST(std::vector<Token> tokens) {
    AST ast;
    ParserState state{0, tokens};

    while (state.peek().type != tokens::eof) {
        Token actual = state.peek();

        switch (actual.type) {
            case tokens::var: {
                state.consume(); // consume var
                
                Token name_token = state.consume(); // consume name

                if (state.peek().type != tokens::equal) {
                    throw std::runtime_error("Bolt Syntax Error: expected '=' after variable name");
                }
                state.consume(); // consume =

                VarDecl vardecl;
                vardecl.name_index = ast.add_string(name_token.value);

                vardecl.initializer = parse_expression(state, ast);

                ast.add_node(Node{vardecl});
                break;
            }
            case tokens::eof: {
                goto eof;
                break;
            }
            default:
                state.consume();
                break;
        }
    }
    eof: ;

    return ast;
}
