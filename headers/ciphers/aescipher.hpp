#pragma once

#include "basecipher.hpp"

namespace uc2
{
class CAesCipher : public IBaseCipher
{
public:
    CAesCipher();
    virtual ~CAesCipher();

    virtual void Initialize(std::string_view key, std::string_view iv,
                            bool paddingEnabled = false);
    virtual std::uint64_t Decrypt(gsl::span<const std::uint8_t> inData,
                                  gsl::span<std::uint8_t> outBuffer);
};
}  // namespace uc2
