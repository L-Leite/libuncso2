#include "pkg/pkgentryimpl.hpp"

#include <assert.h>
#include <algorithm>
#include <vector>

#include <ciphers/aescipher.hpp>
#include "decryptor.hpp"
#include "keyhashes.hpp"

static std::string MakeUnixSeparated(std::string_view inPath)
{
    constexpr const char rootCharacter = '/';

    std::string szNewPath;
    szNewPath.reserve(sizeof(rootCharacter) + inPath.length());
    szNewPath = rootCharacter;
    szNewPath += inPath.data();
    std::replace(szNewPath.begin(), szNewPath.end(), '\\', '/');

    return szNewPath;
}

template <typename NumType,
          typename NoConstNumType = typename std::remove_const<NumType>::type>
constexpr inline NoConstNumType RoundNumberToBlock(const NumType num)
{
    return (num % 16 == 0) ? num : (16 - num % 16) + num;
}

namespace uc2
{
constexpr const size_t PKG_ENTRY_KEY_LEN = 16;
constexpr const uint64_t PKG_DATA_BLOCK_SIZE = 0x10000;

PkgEntryImpl::PkgEntryImpl(std::string_view szFilePath, uint64_t pkgFileOffset,
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

        fs::path filePath = this->m_szFilePath;
        this->m_szHashedKey =
            GeneratePkgFileKey(filePath.filename().string(), szvPkgKey);
        this->m_szHashedKey.resize(PKG_ENTRY_KEY_LEN);
    }
}

PkgEntryImpl::~PkgEntryImpl() {}

std::pair<uint8_t*, uint64_t> PkgEntryImpl::DecryptFile(
    const uint64_t iBytesToDecrypt /*= 0 */)
{
    if (this->m_FileDataView.empty() == true)
    {
        throw std::invalid_argument(
            "libuncso2: The entry's file data is empty.");
    }

    const bool bDecryptAll = iBytesToDecrypt == 0;
    const uint64_t iAlignedBytes =
        bDecryptAll == true ? 0 : RoundNumberToBlock(iBytesToDecrypt);
    const uint64_t iRequiredDataSize =
        bDecryptAll == true ? this->m_iEncryptedSize : iAlignedBytes;

    const uint64_t iRequiredFileSize =
        this->m_iPkgFileOffset + iRequiredDataSize;
    const uint64_t iFileDataSize = this->m_FileDataView.size_bytes();

    if (iRequiredFileSize > iFileDataSize)
    {
        throw std::runtime_error("libuncso2: The file in this entry cannot be "
                                 "larger than the pkg file");
    }

    if (this->IsEncrypted() == true)
    {
        return this->HandleEncryptedFile(iAlignedBytes);
    }
    else
    {
        return this->HandlePlainFile(iAlignedBytes);
    }
}

const std::string_view PkgEntryImpl::GetFilePath()
{
    return this->m_szFilePath;
}

uint64_t PkgEntryImpl::GetPkgFileOffset()
{
    return this->m_iPkgFileOffset;
}

uint64_t PkgEntryImpl::GetEncryptedSize()
{
    return this->m_iEncryptedSize;
}

uint64_t PkgEntryImpl::GetDecryptedSize()
{
    return this->m_iDecryptedSize;
}

bool PkgEntryImpl::IsEncrypted()
{
    return this->m_bIsEncrypted;
}

std::pair<uint8_t*, uint64_t> PkgEntryImpl::HandleEncryptedFile(
    const uint64_t iBytesToDecrypt) const
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

    bool bDecryptAll = iBytesToDecrypt == 0;

    const uint64_t iTargetEncDataSize =
        bDecryptAll == true ? this->m_iEncryptedSize : iBytesToDecrypt;
    const uint64_t iTargetDecDataSize =
        bDecryptAll == true ? this->m_iDecryptedSize : iBytesToDecrypt;

    // The data must be decrypted each PKG_DATA_BLOCK_SIZE (which at the
    // time of writing this is 65536), or else only the first 65536
    // bytes will be correct
    for (uint64_t curOff = 0; curOff < iTargetEncDataSize;
         curOff += PKG_DATA_BLOCK_SIZE)
    {
        uint8_t* pBlock = reinterpret_cast<uint8_t*>(dwBlockStart + curOff);
        const uint64_t iCurBlockSize =
            std::min(iTargetEncDataSize - curOff, PKG_DATA_BLOCK_SIZE);

        decryptor.DecryptInBuffer(pBlock, iCurBlockSize);
    }

    return { pFileStart, iTargetDecDataSize };
}

std::pair<uint8_t*, uint64_t> PkgEntryImpl::HandlePlainFile(
    const uint64_t iBytesToDecrypt) const noexcept
{
    bool bDecryptAll = iBytesToDecrypt == 0;

    const uint64_t iTargetDecDataSize =
        bDecryptAll == true ? this->m_iDecryptedSize : iBytesToDecrypt;

    uint64_t dwBlockStart =
        reinterpret_cast<uint64_t>(this->m_FileDataView.data()) +
        this->m_iPkgFileOffset;
    uint8_t* pFileStart = reinterpret_cast<uint8_t*>(dwBlockStart);
    return { pFileStart, iTargetDecDataSize };
}

void PkgEntryImpl::SetDataBufferView(gsl::span<uint8_t> newDataView)
{
    this->m_FileDataView = newDataView;
}

void PkgEntryImpl::ReleaseDataBufferView()
{
    this->m_FileDataView = gsl::span<uint8_t>();
}
}  // namespace uc2