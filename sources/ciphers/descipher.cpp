#include "ciphers/descipher.hpp"

#include <des.h>
#include <filters.h>
#include <modes.h>

namespace uc2
{
CDesCipher::CDesCipher() {}

CDesCipher::~CDesCipher() {}

void CDesCipher::Initialize(std::string_view key, std::string_view iv,
                            bool paddingEnabled /*= false*/)
{
    this->m_szvKey = key;
    this->m_szvIV = iv;
    this->m_bPaddingEnabled = paddingEnabled;
}

uint64_t CDesCipher::Decrypt(gsl::span<const std::uint8_t> inData,
                             gsl::span<std::uint8_t> outBuffer)
{
    CryptoPP::CBC_Mode<CryptoPP::DES>::Decryption dec;

    dec.SetKeyWithIV(reinterpret_cast<const uint8_t*>(this->m_szvKey.data()),
                     this->m_szvKey.length() / 2,
                     reinterpret_cast<const uint8_t*>(this->m_szvIV.data()));

    auto scheme = this->m_bPaddingEnabled ?
                      CryptoPP::BlockPaddingSchemeDef::DEFAULT_PADDING :
                      CryptoPP::BlockPaddingSchemeDef::NO_PADDING;

    auto sink =
        new CryptoPP::ArraySink(outBuffer.data(), outBuffer.size_bytes());
    auto filter = new CryptoPP::StreamTransformationFilter(dec, sink, scheme);

    CryptoPP::StringSource source(inData.data(), inData.size_bytes(), true,
                                  filter);

    return sink->TotalPutLength();
}
}  // namespace uc2
