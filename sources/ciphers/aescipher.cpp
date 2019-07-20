#include "ciphers/aescipher.hpp"

#include <aes.h>
#include <filters.h>
#include <modes.h>

namespace uc2
{
CAesCipher::CAesCipher() {}

CAesCipher::~CAesCipher() {}

void CAesCipher::Initialize(std::string_view key, std::string_view iv,
                            bool paddingEnabled /*= false*/)
{
    this->m_szvKey = key;
    this->m_szvIV = iv;
    this->m_bPaddingEnabled = paddingEnabled;
}

uint64_t CAesCipher::Decrypt(const void* pStart, void* pOutBuffer,
                             const uint64_t iLength)
{
    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption dec;

    dec.SetKeyWithIV(reinterpret_cast<const uint8_t*>(this->m_szvKey.data()),
                     this->m_szvKey.length(),
                     reinterpret_cast<const uint8_t*>(this->m_szvIV.data()));

    auto scheme = this->m_bPaddingEnabled ?
                      CryptoPP::BlockPaddingSchemeDef::DEFAULT_PADDING :
                      CryptoPP::BlockPaddingSchemeDef::NO_PADDING;

    CryptoPP::StreamTransformationFilter filter(dec, nullptr, scheme);
    filter.Put(static_cast<const uint8_t*>(pStart), iLength);
    filter.MessageEnd();

    const size_t iNewLength = filter.MaxRetrievable();
    filter.Get(static_cast<uint8_t*>(pOutBuffer), iLength);

    return iNewLength;
}
}  // namespace uc2