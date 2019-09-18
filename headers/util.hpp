#pragma once

#include <cstdint>

namespace uc2
{
template <class T>
constexpr inline T* AddOffsetToBase(void* base, const std::uint64_t offset = 0)
{
    std::uint64_t convertedBase = reinterpret_cast<std::uint64_t>(base);
    return reinterpret_cast<T*>(convertedBase + offset);
}

template <class T>
constexpr inline const T* AddOffsetToBase(const void* base,
                                          const std::uint64_t offset = 0)
{
    const std::uint64_t convertedBase =
        reinterpret_cast<const std::uint64_t>(base);
    return reinterpret_cast<const T*>(convertedBase + offset);
}
}  // namespace uc2
