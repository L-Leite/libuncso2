#include "pkg/pkgindeximpl.hpp"

#include <stdexcept>

#include "decryptor.hpp"
#include "keyhashes.hpp"
#include "pkg/pkgstructures.hpp"
#include "util.hpp"

namespace uc2
{
constexpr const uint16_t SUPPORTED_PKG_VERSION = 2;

std::vector<std::string_view> SplitTextFileByLine(gsl::span<uint8_t> fileBuffer)
{
    constexpr std::string_view szNewLine("\r\n", 2);

    std::vector<std::string_view> vFilenames;

    std::string_view szPkgBuffer(
        reinterpret_cast<const char*>(fileBuffer.data()), fileBuffer.size());
    uint64_t iCurrentPos = 0;
    uint64_t iLineEndPos = 0;

    while ((iLineEndPos = szPkgBuffer.find(szNewLine, iCurrentPos)) !=
           std::string::npos)
    {
        auto strBase = AddOffsetToBase<char>(szPkgBuffer.data(), iCurrentPos);
        std::string_view szvEntry(strBase, iLineEndPos - iCurrentPos);

        vFilenames.push_back(szvEntry);

        iCurrentPos = iLineEndPos + szNewLine.length();
    }

    return vFilenames;
}

PkgIndex::ptr_t PkgIndex::Create(std::string_view indexFilename,
                                 std::vector<uint8_t>& fileData,
                                 const uint8_t (&keyCollection)[4][16])
{
    return std::make_unique<PkgIndexImpl>(indexFilename, fileData,
                                          keyCollection);
}

PkgIndex::ptr_t PkgIndexImpl::CreateSpan(
    std::string_view indexFilename, gsl::span<uint8_t> fileDataView,
    gsl::span<const uint8_t[4][16]> keyCollectionView)
{
    return std::make_unique<PkgIndexImpl>(indexFilename, fileDataView,
                                          keyCollectionView);
}

PkgIndexImpl::PkgIndexImpl(std::string_view indexFilename,
                           std::vector<uint8_t>& fileData,
                           const uint8_t (&keyCollection)[4][16])
    : m_szvIndexFilename(indexFilename), m_FileDataView(fileData),
      m_KeyCollectionView(&keyCollection, 16 * 4)
{
    this->ValidateHeader();
}

PkgIndexImpl::PkgIndexImpl(std::string_view indexFilename,
                           gsl::span<uint8_t> fileDataView,
                           gsl::span<const uint8_t[4][16]> keyCollectionView)
    : m_szvIndexFilename(indexFilename), m_FileDataView(fileDataView),
      m_KeyCollectionView(keyCollectionView)
{
    this->ValidateHeader();
}

PkgIndexImpl::~PkgIndexImpl() {}

uint64_t PkgIndexImpl::Parse()
{
    auto pHeader =
        AddOffsetToBase<PkgIndexHeader_t>(this->m_FileDataView.data());

    std::vector<uint8_t> digestedKey = GeneratePkgIndexKey(
        pHeader->iKey, this->m_szvIndexFilename, this->m_KeyCollectionView);

    auto pDataStart = AddOffsetToBase<uint8_t>(this->m_FileDataView.data(),
                                               sizeof(PkgIndexHeader_t));

    auto pCipher = CreateIndexCipher(pHeader->iCipher);
    CDecryptor decryptor(pCipher.get(), digestedKey);

    uint64_t iNewDataSize =
        decryptor.DecryptInBuffer(pDataStart, pHeader->iFileSize);

    this->m_vFilenames =
        SplitTextFileByLine({ pDataStart, pHeader->iFileSize });

    const uint64_t iNewSize = sizeof(PkgIndexHeader_t) + iNewDataSize;
    return iNewSize;
}

const std::vector<std::string_view>& PkgIndexImpl::GetFilenames()
{
    return m_vFilenames;
}

void PkgIndexImpl::ValidateHeader()
{
    const uint64_t iFileDataSize = this->m_FileDataView.size_bytes();

    if (iFileDataSize < sizeof(PkgIndexHeader_t))
    {
        throw std::range_error(
            "libuncso2: The index file does not have a header");
    }

    auto pHeader =
        AddOffsetToBase<PkgIndexHeader_t>(this->m_FileDataView.data());

    if (pHeader->iVersion != SUPPORTED_PKG_VERSION)
    {
        throw std::runtime_error(
            "libuncso2: The index file's header is not supported");
    }

    if (iFileDataSize != pHeader->iFileSize + sizeof(PkgIndexHeader_t))
    {
        throw std::length_error("libuncso2: The file size in the header does "
                                "not match the real index's file size");
    }
}
}  // namespace uc2
