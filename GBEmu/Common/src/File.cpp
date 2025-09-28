#include "File.h"

#include "Assert.h"

#include <fstream>

namespace Common
{
std::vector<char> ReadBinaryFile(const std::string& path)
{
    std::vector<char> buffer;
    std::ifstream file(path, std::ios::ate | std::ios::binary);
    GBE_ASSERT_OR_EXECUTE(file.is_open(), "Failed to open file!", return buffer);

    const U64 fileSize = static_cast<U64>(file.tellg());
    buffer.resize(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);
    file.close();

    return buffer;
}
} // namespace Common
