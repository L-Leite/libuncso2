#pragma once

#include "pkgfile.hpp"

#include <gsl/gsl>
#include <string>

namespace uc2
{
class PkgFileImpl : public PkgFile
{
public:
    PkgFileImpl(std::string_view szvFilename, std::vector<uint8_t>& fileData,
                std::string_view szvEntryKey, std::string_view szvDataKey,
                PkgFileOptions* options = nullptr);
    PkgFileImpl(std::string_view szvFilename, gsl::span<uint8_t> fileDataView,
                std::string_view szvEntryKey, std::string_view szvDataKey,
                PkgFileOptions* pOptions = nullptr);
    virtual ~PkgFileImpl();

    virtual void Parse();

    virtual std::vector<entryptr_t>& GetEntries();

    static ptr_t CreateSpan(std::string_view szvFilename,
                            gsl::span<uint8_t> fileDataView,
                            std::string_view szvEntryKey,
                            std::string_view szvDataKey,
                            PkgFileOptions* pOptions = nullptr);

private:
    void Initialize(std::string_view szvEntryKey, PkgFileOptions* pOptions);

    template <typename PkgHeaderType>
    void ValidateInit();

    template <typename PkgHeaderType>
    void DecryptHeader();
    template <typename PkgHeaderType>
    void ParseEntries();

    template <typename T>
    T* GetData(uint64_t offset = 0);

private:
    bool m_bIsTfoPkg;

    std::string_view m_szvFilename;
    std::string m_szHashedEntryKey;
    std::string_view m_szvDataKey;

    gsl::span<uint8_t> m_FileDataView;

    std::vector<std::unique_ptr<PkgEntry>> m_Entries;
};
}  // namespace uc2
