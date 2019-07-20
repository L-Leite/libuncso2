#pragma once

#include <memory>
#include <string_view>
#include <vector>

#include "ciphers/basecipher.hpp"

using namespace std::string_view_literals;

namespace uc2
{
enum
{
    CIPHER_DES = 1,
    CIPHER_AES,
    CIPHER_BLOWFISH,
};

std::unique_ptr<IBaseCipher> CreateIndexCipher(int cipher);

class CDecryptor
{
public:
    CDecryptor(IBaseCipher* cipher, std::string_view key, bool paddingEnabled);
    CDecryptor(IBaseCipher* cipher, std::string_view key,
               std::string_view iv = {}, bool paddingEnabled = true);
    CDecryptor(IBaseCipher* cipher, const std::vector<uint8_t>& key,
               const std::vector<uint8_t>& iv = {}, bool paddingEnabled = true);
    ~CDecryptor() = default;

    std::vector<uint8_t> Decrypt(std::vector<uint8_t>& data) const;

    std::vector<uint8_t> Decrypt(const void* pStart,
                                 const size_t iLength) const;

    size_t Decrypt(const void* pStart, void* pOutBuffer,
                   const size_t iLength) const;

    size_t DecryptInBuffer(void* pBuffer, const size_t iLength) const;

private:
    void Initialize(std::string_view key, std::string_view iv,
                    bool paddingEnabled);

private:
    IBaseCipher* m_pCipher;

private:
    CDecryptor() = delete;
};
}  // namespace uc2
