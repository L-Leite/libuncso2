#include "pkgfile.h"
#include "pkg/pkgfileimpl.hpp"

#ifdef __cplusplus
extern "C"
{
    PkgFile_t UNCSO2_CALLMETHOD uncso2_PkgFile_Create(
        const char* filename, void* dataBuffer, uint64_t dataSize,
        const char* szEntryKey, const char* szDataKey,
        PkgFileOptions_t options /*= NULL*/)
    {
        gsl::span<uint8_t> dataView(reinterpret_cast<uint8_t*>(dataBuffer),
                                    dataSize);

        auto pOptions = reinterpret_cast<uc2::PkgFileOptions*>(options);

        try
        {
            auto newPkg = uc2::PkgFileImpl::CreateSpan(
                filename, dataView, szEntryKey, szDataKey, pOptions);
            return reinterpret_cast<PkgFile_t>(newPkg.release());
        }
        catch (const std::exception& e)
        {
            return NULL;
        }
    }

    void UNCSO2_CALLMETHOD uncso2_PkgFile_Free(PkgFile_t pkgHandle)
    {
        auto pPkg = reinterpret_cast<uc2::PkgFile*>(pkgHandle);
        delete pPkg;
    }

    bool UNCSO2_CALLMETHOD uncso2_PkgFile_Parse(PkgFile_t pkgHandle)
    {
        if (pkgHandle == NULL)
        {
            return false;
        }

        auto pPkg = reinterpret_cast<uc2::PkgFile*>(pkgHandle);

        try
        {
            pPkg->Parse();
            return true;
        }
        catch (const std::exception& e)
        {
            return false;
        }
    }

    uint64_t UNCSO2_CALLMETHOD uncso2_PkgFile_GetEntriesNum(PkgFile_t pkgHandle)
    {
        if (pkgHandle == NULL)
        {
            return 0;
        }

        auto pPkg = reinterpret_cast<uc2::PkgFile*>(pkgHandle);

        try
        {
            return pPkg->GetEntries().size();
        }
        catch (const std::exception& e)
        {
            return 0;
        }
    }

    PkgEntry_t* UNCSO2_CALLMETHOD uncso2_PkgFile_GetEntries(PkgFile_t pkgHandle)
    {
        if (pkgHandle == NULL)
        {
            return 0;
        }

        auto pPkg = reinterpret_cast<uc2::PkgFile*>(pkgHandle);

        try
        {
            return reinterpret_cast<PkgEntry_t*>(pPkg->GetEntries().data());
        }
        catch (const std::exception& e)
        {
            return 0;
        }
    }
#endif

#ifdef __cplusplus
}
#endif