#include "pkg/pkgentryimpl.hpp"

#include <assert.h>
#include <algorithm>
#include <vector>

#include <ciphers/aescipher.hpp>
#include "decryptor.hpp"
#include "keyhashes.hpp"

std::string MakeUnixSeparated(const char* inPath)
{
    std::string szNewPath = inPath;
    std::replace(szNewPath.begin(), szNewPath.end(), '\\', '/');
    return szNewPath;
}

namespace uc2
{
constexpr const size_t PKG_ENTRY_KEY_LEN = 16;
constexpr const uint64_t PKG_DATA_BLOCK_SIZE = 0x10000;

PkgEntryImpl::PkgEntryImpl(const char* szFilePath, uint64_t pkgFileOffset,
                           uint64_t encryptedSize, uint64_t decryptedSize,
                           bool isEncrypted, gsl::span<uint8_t> fileDataView,
                           std::string_view szvPkgKey /*= {}*/)
    : m_FileDataView(fileDataView), m_szFilePath(MakeUnixSeparated(szFilePath)),
      m_iPkgFileOffset(pkgFileOffset), m_iEncryptedSize(encryptedSize),
      m_iDecryptedSize(decryptedSize), m_bIsEncrypted(isEncrypted)
{
    if (isEncrypted == true)
    {
        // Packed size should be the same or bigger than unpacked size
        if (decryptedSize > encryptedSize)
        {
            throw std::invalid_argument("libuncso2: The decrypted size is "
                                        "bigger than the encrypted size");
        }
    }

    const uint64_t iRequiredFileSize = pkgFileOffset + encryptedSize;
    const uint64_t iFileDataSize = this->m_FileDataView.size_bytes();

    if (iRequiredFileSize > iFileDataSize)
    {
        throw std::runtime_error("libuncso2: The file in this entry cannot be "
                                 "larger than the pkg file");
    }

    if (isEncrypted == true)
    {
        fs::path filePath = this->m_szFilePath;
        this->m_szHashedKey =
            GeneratePkgFileKey(filePath.filename().string(), szvPkgKey);
        this->m_szHashedKey.resize(PKG_ENTRY_KEY_LEN);
    }
}

PkgEntryImpl::~PkgEntryImpl() {}

std::pair<uint8_t*, uint64_t> PkgEntryImpl::DecryptFile()
{
    if (this->IsEncrypted() == true)
    {
        return this->HandleEncryptedFile();
    }

    return this->HandlePlainFile();
}

std::pair<uint8_t*, uint64_t> PkgEntryImpl::HandleEncryptedFile()
{
    if (this->m_iEncryptedSize == 0)
    {
        return { nullptr, 0 };
    }

    uint64_t dwBlockStart =
        reinterpret_cast<uint64_t>(this->m_FileDataView.data()) +
        this->m_iPkgFileOffset;
    uint8_t* pFileStart = reinterpret_cast<uint8_t*>(dwBlockStart);

    CAesCipher cipher;
    CDecryptor decryptor(&cipher, this->m_szHashedKey, false);

    // The data must be decrypted each PKG_DATA_BLOCK_SIZE (which at the time of
    // writing this is 65536), or else only the first 65536 bytes will be
    // correct
    for (uint64_t curOff = 0; curOff < this->m_iEncryptedSize;
         curOff += PKG_DATA_BLOCK_SIZE)
    {
        uint8_t* pBlock = reinterpret_cast<uint8_t*>(dwBlockStart + curOff);
        const uint64_t iCurBlockSize =
            std::min(this->m_iEncryptedSize - curOff, PKG_DATA_BLOCK_SIZE);

        decryptor.DecryptInBuffer(pBlock, iCurBlockSize);
    }

    return { pFileStart, this->m_iDecryptedSize };
}

std::pair<uint8_t*, uint64_t> PkgEntryImpl::HandlePlainFile()
{
    uint64_t dwBlockStart =
        reinterpret_cast<uint64_t>(this->m_FileDataView.data()) +
        this->m_iPkgFileOffset;
    uint8_t* pFileStart = reinterpret_cast<uint8_t*>(dwBlockStart);
    return { pFileStart, this->m_iDecryptedSize };
}
}  // namespace uc2