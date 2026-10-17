#include <string>
#include <vector>

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

        switch (actual) {
            case '+':
                t.type = tokens::plus;
                i++;
                break;
            case '-':
                t.type = tokens::minus;
                i++;
                break;
            case '*':
                t.type = tokens::star;
                i++;
                break;
            case '/':
                t.type = tokens::slash;
                i++;
                break;
            case '=':
                t.type = tokens::equal;
                i++;
                break;
            default: {
                std::string buffer = "";
                while (i < length && src[i] != ' ' && src[i] != '+' && src[i] != '-' && src[i] != '*' && src[i] != '/') {
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
                } else {
                    i++; 
                    continue;
                }
                break;
            }
        }

        result.push_back(t);
    }

    return result;
}