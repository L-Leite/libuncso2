#pragma once

#include "pkgindex.hpp"

#include <gsl/gsl>

namespace uc2
{
struct PkgIndexHeader_t;

class PkgIndexImpl : public PkgIndex
{
public:
    PkgIndexImpl(std::string_view indexFilename, std::vector<uint8_t>& fileData,
                 const uint8_t (*keyCollection)[4][16]);
    PkgIndexImpl(std::string_view indexFilename,
                 gsl::span<uint8_t> fileDataView,
                 gsl::span<const uint8_t[4][16]> keyCollectionView);
    virtual ~PkgIndexImpl() override;

    virtual void SetKeyCollection(
        const uint8_t (*keyCollection)[4][16]) override;
    void SetKeyCollectionSpan(
        gsl::span<const uint8_t[4][16]> keyCollectionView);

    virtual void ValidateHeader() override;

    virtual uint64_t Parse() override;

    virtual const std::vector<std::string_view>& GetFilenames() override;

    static ptr_t CreateSpan(std::string_view indexFilename,
                            gsl::span<uint8_t> fileDataView,
                            gsl::span<const uint8_t[4][16]> keyCollectionView);

private:
    std::string_view m_szvIndexFilename;
    gsl::span<uint8_t> m_FileDataView;
    gsl::span<const uint8_t[4][16]> m_KeyCollectionView;

    std::vector<std::string_view> m_vFilenames;

    bool m_bHeaderValidated;
};
}  // namespace uc2
