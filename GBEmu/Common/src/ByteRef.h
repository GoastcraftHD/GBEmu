#pragma once

#include "Types.h"

#include <atomic>

namespace Common
{
class ByteRef
{
public:
    ByteRef(U8& byte, std::atomic<bool>& dataChanged) : m_Byte(byte), m_DataChanged(dataChanged) {}

    ByteRef& operator=(U8 value)
    {
        m_Byte = value;
        m_DataChanged = true;
        return *this;
    }

    ByteRef& operator++(int)
    {
        m_Byte++;
        m_DataChanged = true;
        return *this;
    }

    ByteRef& operator--(int)
    {
        m_Byte--;
        m_DataChanged = true;
        return *this;
    }

    operator U8() const
    {
        return m_Byte;
    }

private:
    U8& m_Byte;
    std::atomic<bool>& m_DataChanged;
};
} // namespace Common
