#pragma once

#include "basecipher.hpp"

namespace uc2
{
class CDesCipher : public IBaseCipher
{
public:
    CDesCipher();
    virtual ~CDesCipher();

    virtual void Initialize(std::string_view key, std::string_view iv,
                            bool paddingEnabled = false);
    virtual uint64_t Decrypt(const void* pStart, void* pOutBuffer,
                             const uint64_t iSize);

protected:
    std::string_view m_szvKey;
    std::string_view m_szvIV;
    bool m_bPaddingEnabled;
};
}  // namespace uc2
