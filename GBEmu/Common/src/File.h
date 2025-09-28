#pragma once

#include "Types.h"

#include <string>
#include <vector>

namespace Common
{
std::vector<char> ReadBinaryFile(const std::string& path);
} // namespace Common
