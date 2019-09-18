#pragma once

#include <cstdint>
#include <gsl/gsl>
#include <string_view>

namespace uc2
{
class IBaseCipher
{
public:
    virtual ~IBaseCipher() = default;
    virtual void Initialize(std::string_view key, std::string_view iv,
                            bool paddingEnabled = false) = 0;
    virtual std::uint64_t Decrypt(gsl::span<const std::uint8_t> inData,
                                  gsl::span<std::uint8_t> outBuffer) = 0;

protected:
    std::string_view m_szvKey;
    std::string_view m_szvIV;
    bool m_bPaddingEnabled;
};
}  // namespace uc2
