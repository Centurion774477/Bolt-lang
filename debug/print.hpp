#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../frontend/lexer/tokens.hpp"

std::string_view tokenToString(tokens type);

void show(std::vector<Token> vec);