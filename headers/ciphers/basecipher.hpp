#pragma once

#include <stdint.h>
#include <string_view>

namespace uc2
{
class IBaseCipher
{
public:
    virtual ~IBaseCipher() = default;
    virtual void Initialize(std::string_view key, std::string_view iv,
                            bool paddingEnabled = false) = 0;
    virtual uint64_t Decrypt(const void* pStart, void* pOutBuffer,
                             const uint64_t iSize) = 0;
};
}  // namespace uc2
