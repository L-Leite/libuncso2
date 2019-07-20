#pragma once

#include <stdint.h>

namespace uc2
{
template <class T>
constexpr inline T* AddOffsetToBase(void* base, const uint64_t offset = 0)
{
    uint64_t convertedBase = reinterpret_cast<uint64_t>(base);
    return reinterpret_cast<T*>(convertedBase + offset);
}

template <class T>
constexpr inline const T* AddOffsetToBase(const void* base,
                                          const uint64_t offset = 0)
{
    const uint64_t convertedBase = reinterpret_cast<const uint64_t>(base);
    return reinterpret_cast<const T*>(convertedBase + offset);
}
}  // namespace uc2
