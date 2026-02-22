#pragma once
#include "Bytecode.h"
#include <string>

std::string generateCppFromBytecode(const std::vector<Instruction>& code);
