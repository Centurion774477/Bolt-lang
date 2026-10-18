#pragma once

#include "../../frontend/astgen/astgen.hpp"
#include "../../frontend/lexer/tokens.hpp"
#include "../../common/bytecode.h"

#include <string>
#include <fstream>
#include <cstdint>
#include <vector>
#include <variant>
#include <iostream>

int generateBytecode(AST ast);
