#include "RAM.h"

namespace Emulator
{
RAM::RAM()
{
    m_RawData = std::vector<U8>(0xFFFF);
}
} // namespace Emulator
