#include "RAM.h"

namespace Emulator
{
RAM::RAM()
{
    m_RawData = std::vector<U8>(0x2000); // 8KiB RAM
}
} // namespace Emulator
