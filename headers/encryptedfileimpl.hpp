#pragma once

#include "encryptedfile.hpp"

#include <gsl/gsl>

namespace uc2
{
#pragma pack(push, 1)
struct EncryptedFileHeader_t
{
    char checksum[10];
    uint16_t version;
    uint8_t cipher;
    uint8_t flag;
    uint32_t fileSize;
};
#pragma pack(pop)

class EncryptedFileImpl : public EncryptedFile
{
public:
    EncryptedFileImpl(std::string_view fileName, std::vector<uint8_t>& fileData,
                      const uint8_t (&keyCollection)[4][16]);
    EncryptedFileImpl(std::string_view fileName,
                      gsl::span<uint8_t> fileDataView,
                      gsl::span<const uint8_t[4][16]> keyCollectionView);
    virtual ~EncryptedFileImpl();

    virtual std::pair<uint8_t*, size_t> Decrypt();

    static ptr_t CreateSpan(std::string_view fileName,
                            gsl::span<uint8_t> fileDataView,
                            gsl::span<const uint8_t[4][16]> keyCollectionView);

private:
    bool IsHeaderValid() const;

private:
    std::string_view m_szvFileName;
    gsl::span<uint8_t> m_FileDataView;
    gsl::span<const uint8_t[4][16]> m_KeyCollectionView;
};
}  // namespace uc2
