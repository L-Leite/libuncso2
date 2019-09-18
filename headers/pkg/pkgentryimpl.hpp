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
    PkgEntryImpl(std::string_view filePath, uint64_t pkgFileOffset,
                 uint64_t encryptedSize, uint64_t decryptedSize,
                 bool isEncrypted, gsl::span<uint8_t> fileData,
                 std::string_view szvPkgKey = {});
    virtual ~PkgEntryImpl() override;

public:
    virtual std::pair<uint8_t*, uint64_t> DecryptFile(
        const uint64_t iBytesToDecrypt = 0) override;

    virtual const std::string_view GetFilePath() override;
    virtual uint64_t GetPkgFileOffset() override;
    virtual uint64_t GetEncryptedSize() override;
    virtual uint64_t GetDecryptedSize() override;
    virtual bool IsEncrypted() override;

    void SetDataBufferView(gsl::span<uint8_t> newDataView);
    void ReleaseDataBufferView();

private:
    std::pair<uint8_t*, uint64_t> HandleEncryptedFile(
        const uint64_t iBytesToDecrypt) const;
    std::pair<uint8_t*, uint64_t> HandlePlainFile(
        const uint64_t iBytesToDecrypt) const noexcept;

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
