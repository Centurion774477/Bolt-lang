#include <string>
#include <vector>
#include <unordered_map>

#include "tokens.hpp"

std::unordered_map<std::string, int> keyword_mapping = {{"var", 0}};

std::vector<Token> tokenize(std::string src) {
    std::vector<Token> result;
    size_t i = 0;
    size_t length = src.size();

    while (i < length) {
        char actual = src[i];
        Token t;

        if (actual == ' ' || actual == '\t' || actual == '\n' || actual == '\r') {
            i++;
            continue;
        }

        bool is_single_char = true;
        switch (actual) {
            case '+': t.type = tokens::plus; break;
            case '-': t.type = tokens::minus; break;
            case '*': t.type = tokens::star; break;
            case '/': t.type = tokens::slash; break;
            case '=': t.type = tokens::equal; break;
            default:
                is_single_char = false;
                break;
        }

        if (is_single_char) {
            i++; 
            result.push_back(t);
            continue;
        }

        std::string buffer = "";
        while (i < length && src[i] != ' ' && src[i] != '\t' && src[i] != '\n' && src[i] != '\r' &&
               src[i] != '+' && src[i] != '-' && src[i] != '*' && src[i] != '/' && src[i] != '=') {
            buffer += src[i];
            i++;
        }

        if (!buffer.empty()) {
            if (keyword_mapping.count(buffer) && keyword_mapping[buffer] == 0) {
                t.type = tokens::var;
            } else if (buffer.size() >= 2 && 
                       (buffer.front() == buffer.back()) && 
                       (buffer.front() == '"' || buffer.front() == '\'')) {
                t.type = tokens::c_str;
                buffer.pop_back();
                buffer.erase(0, 1);
                t.value = buffer;
            } else { 
                t.type = tokens::identifier;
                t.value = buffer;
            }
            result.push_back(t);
        } else {
            i++;
        }
    }

    return result;
}
