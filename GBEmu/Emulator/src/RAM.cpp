#include "RAM.h"

namespace Emulator
{
RAM::RAM(const std::vector<char>& romData) : m_RawData(std::vector<U8>(0xFFFF))
{
    std::memcpy(m_RawData.data(), romData.data(), romData.size());
}
} // namespace Emulator
