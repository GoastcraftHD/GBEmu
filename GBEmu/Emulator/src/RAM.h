#pragma once

#include "Types.h"

#include <vector>

namespace Emulator
{
class RAM
{
public:
    RAM();

    U8& operator[](U16 address)
    {
        return m_RawData[address];
    }

    const U8& operator[](U16 address) const
    {
        return m_RawData[address];
    }

private:
    std::vector<U8> m_RawData;
};
} // namespace Emulator
