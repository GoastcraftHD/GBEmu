#pragma once

#include "ByteRef.h"
#include "Types.h"

#include <atomic>
#include <vector>

namespace Emulator
{
class RAM
{
public:
    RAM() = default;
    RAM(const std::vector<char>& romData);

    const std::vector<U8>& GetRawData() const
    {
        return m_RawData;
    }

    Common::ByteRef operator[](U16 address)
    {
        return Common::ByteRef(m_RawData[address], m_DataChanged);
    }

    const U8& operator[](U16 address) const
    {
        return m_RawData[address];
    }

private:
    std::vector<U8> m_RawData;
    std::atomic<bool> m_DataChanged;
};
} // namespace Emulator
