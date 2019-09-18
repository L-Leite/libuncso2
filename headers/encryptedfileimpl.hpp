#pragma once

#include "encryptedfile.hpp"

#include <gsl/gsl>

namespace uc2
{
#pragma pack(push, 1)
struct EncryptedFileHeader_t
{
    char checksum[10];
    std::uint16_t version;
    std::uint8_t cipher;
    std::uint8_t flag;
    std::uint32_t fileSize;
};
#pragma pack(pop)

static_assert(sizeof(EncryptedFileHeader_t) == 18,
              "The encrypted file's header must be 18 bytes long!");

class EncryptedFileImpl : public EncryptedFile
{
public:
    EncryptedFileImpl(std::string_view fileName,
                      std::vector<std::uint8_t>& fileData,
                      const std::uint8_t (&keyCollection)[4][16]);
    EncryptedFileImpl(std::string_view fileName,
                      gsl::span<std::uint8_t> fileDataView,
                      gsl::span<const std::uint8_t[4][16]> keyCollectionView);
    virtual ~EncryptedFileImpl() override;

    virtual std::pair<std::uint8_t*, std::size_t> Decrypt() override;

    static ptr_t CreateSpan(
        std::string_view fileName, gsl::span<std::uint8_t> fileDataView,
        gsl::span<const std::uint8_t[4][16]> keyCollectionView);

private:
    bool IsHeaderValid() const;

private:
    std::string_view m_szvFileName;
    gsl::span<std::uint8_t> m_FileDataView;
    gsl::span<const std::uint8_t[4][16]> m_KeyCollectionView;
};
}  // namespace uc2
