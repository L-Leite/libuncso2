#include "pkg/pkgfileimpl.hpp"

#include <vector>

#include "ciphers/aescipher.hpp"
#include "decryptor.hpp"
#include "keyhashes.hpp"
#include "pkg/pkgentryimpl.hpp"
#include "pkg/pkgfileoptionsimpl.hpp"
#include "pkg/pkgstructures.hpp"

namespace uc2
{
constexpr const size_t PKG_HASHED_ENTRY_KEY_LEN = 16;
constexpr const uint64_t PKG_HEADER_SKIP_HASH_OFFSET = 33;

PkgFile::ptr_t PkgFile::Create(std::string_view szvFilename,
                               std::vector<uint8_t>& fileData,
                               std::string_view szvEntryKey,
                               std::string_view szvDataKey,
                               PkgFileOptions* options /*= nullptr*/)
{
    return std::make_unique<PkgFileImpl>(szvFilename, fileData, szvEntryKey,
                                         szvDataKey, options);
}

PkgFile::ptr_t PkgFileImpl::CreateSpan(std::string_view szvFilename,
                                       gsl::span<uint8_t> fileData,
                                       std::string_view szvEntryKey,
                                       std::string_view szvDataKey,
                                       PkgFileOptions* pOptions /* = nullptr*/)
{
    return std::make_unique<PkgFileImpl>(szvFilename, fileData, szvEntryKey,
                                         szvDataKey, pOptions);
}

PkgFileImpl::PkgFileImpl(std::string_view szvFilename,
                         std::vector<uint8_t>& fileData,
                         std::string_view szvEntryKey,
                         std::string_view szvDataKey,
                         PkgFileOptions* options /* = nullptr*/)
    : m_szvFilename(szvFilename),
      m_szHashedEntryKey(GeneratePkgFileKey(szvFilename, szvEntryKey)),
      m_szvDataKey(szvDataKey), m_FileDataView(fileData)
{
    this->Initialize(szvEntryKey, options);
}

PkgFileImpl::PkgFileImpl(std::string_view szvFilename,
                         gsl::span<uint8_t> fileData,
                         std::string_view szvEntryKey,
                         std::string_view szvDataKey,
                         PkgFileOptions* pOptions /* = nullptr*/)
    : m_szvFilename(szvFilename), m_szHashedEntryKey(),
      m_szvDataKey(szvDataKey), m_FileDataView(fileData)
{
    this->Initialize(szvEntryKey, pOptions);
}

PkgFileImpl::~PkgFileImpl() {}

void PkgFileImpl::Initialize(std::string_view szvEntryKey,
                             PkgFileOptions* pOptions)
{
    if (pOptions)
    {
        this->m_bIsTfoPkg = pOptions->IsTfoPkg();
    }

    if (this->m_bIsTfoPkg)
    {
        this->ValidateInit<PkgHeaderTfo_t>();
    }
    else
    {
        this->ValidateInit<PkgHeader_t>();
    }

    this->m_szHashedEntryKey =
        GeneratePkgFileKey(this->m_szvFilename, szvEntryKey);
    this->m_szHashedEntryKey.resize(PKG_HASHED_ENTRY_KEY_LEN);
}

template <typename PkgHeaderType>
void PkgFileImpl::ValidateInit()
{
    if (this->m_szvFilename.empty() == true)
    {
        throw std::invalid_argument(
            "libuncso2: The file name argument cannot be empty");
    }

    const uint64_t iFileDataSize = this->m_FileDataView.size_bytes();

    if (iFileDataSize < sizeof(PkgHeaderType))
    {
        throw std::range_error(
            "libuncso2: The PKG file does not have a header");
    }
}

void PkgFileImpl::Parse()
{
    if (this->m_bIsTfoPkg)
    {
        this->DecryptHeader<PkgHeaderTfo_t>();
        this->ParseEntries<PkgHeaderTfo_t>();
    }
    else
    {
        this->DecryptHeader<PkgHeader_t>();
        this->ParseEntries<PkgHeader_t>();
    }
}

std::vector<std::unique_ptr<PkgEntry>>& PkgFileImpl::GetEntries()
{
    return this->m_Entries;
}

template <typename PkgHeaderType>
void PkgFileImpl::DecryptHeader()
{
    CAesCipher cipher;
    CDecryptor decryptor(&cipher, this->m_szHashedEntryKey, false);

    auto pPkgHeader = this->GetData<PkgHeaderType>(PKG_HEADER_SKIP_HASH_OFFSET);
    decryptor.DecryptInBuffer(pPkgHeader, sizeof(PkgHeaderType));
}

template <typename PkgHeaderType>
void PkgFileImpl::ParseEntries()
{
    auto pPkgHeader = this->GetData<PkgHeaderType>(PKG_HEADER_SKIP_HASH_OFFSET);
    auto pEntries = this->GetData<PkgEntryHeader_t>(
        PKG_HEADER_SKIP_HASH_OFFSET + sizeof(PkgHeaderType));

    const uint64_t iDataStartOffset =
        PKG_HEADER_SKIP_HASH_OFFSET + sizeof(PkgHeaderType) +
        pPkgHeader->iEntries * sizeof(PkgEntryHeader_t);

    CAesCipher cipher;
    CDecryptor decryptor(&cipher, this->m_szHashedEntryKey, false);

    for (uint32_t i = 0; i < pPkgHeader->iEntries; i++)
    {
        PkgEntryHeader_t entry = pEntries[i];
        decryptor.DecryptInBuffer(&entry, sizeof(PkgEntryHeader_t));

        auto pNewEntry = std::make_unique<PkgEntryImpl>(
            entry.szFilePath, iDataStartOffset + entry.iOffset,
            entry.iEncryptedSize, entry.iDecryptedSize, entry.bIsEncrypted,
            this->m_FileDataView, this->m_szvDataKey);

        this->m_Entries.push_back(std::move(pNewEntry));
    }
}

template <typename T>
T* PkgFileImpl::GetData(uint64_t offset /*= 0*/)
{
    uint64_t data = reinterpret_cast<uint64_t>(this->m_FileDataView.data());
    data += offset;
    return reinterpret_cast<T*>(data);
}
}  // namespace uc2