#pragma once

#include "pkgentry.hpp"

#include <gsl/gsl>
#include <string>
#include <string_view>

namespace uc2
{
class PkgEntryImpl : public PkgEntry
{
public:
    PkgEntryImpl(const char* filePath, uint64_t pkgFileOffset,
                 uint64_t encryptedSize, uint64_t decryptedSize,
                 bool isEncrypted, gsl::span<uint8_t> fileData,
                 std::string_view szvPkgKey = {});
    virtual ~PkgEntryImpl();

public:
    virtual std::pair<uint8_t*, uint64_t> DecryptFile();

    virtual const std::string_view GetFilePath() { return m_szFilePath; }
    virtual uint64_t GetPkgFileOffset() { return m_iPkgFileOffset; }
    virtual uint64_t GetEncryptedSize() { return m_iEncryptedSize; }
    virtual uint64_t GetDecryptedSize() { return m_iDecryptedSize; }
    virtual bool IsEncrypted() { return m_bIsEncrypted; }

private:
    std::pair<uint8_t*, uint64_t> HandlePlainFile();
    std::pair<uint8_t*, uint64_t> HandleEncryptedFile();

private:
    gsl::span<uint8_t> m_FileDataView;

    std::string m_szHashedKey;

    std::string m_szFilePath;
    uint64_t m_iPkgFileOffset;
    uint64_t m_iEncryptedSize;
    uint64_t m_iDecryptedSize;
    bool m_bIsEncrypted;
};
}  // namespace uc2
