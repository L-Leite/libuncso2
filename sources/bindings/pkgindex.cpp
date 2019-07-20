#include "pkgindex.h"
#include "pkg/pkgindeximpl.hpp"

#ifdef __cplusplus
extern "C"
{
    PkgIndex_t UNCSO2_CALLMETHOD uncso2_PkgIndex_Create(
        const char* filename, void* dataBuffer, uint64_t dataSize,
        const uint8_t (*keyCollection)[4][16])
    {
        gsl::span<uint8_t> dataView(reinterpret_cast<uint8_t*>(dataBuffer),
                                    dataSize);

        gsl::span<const uint8_t[4][16]> keyCollectionView(keyCollection,
                                                          16 * 4);

        try
        {
            auto newPkg = uc2::PkgIndexImpl::CreateSpan(filename, dataView,
                                                        keyCollectionView);
            return reinterpret_cast<PkgIndex_t>(newPkg.release());
        }
        catch (const std::exception& e)
        {
            return NULL;
        }
    }

    void UNCSO2_CALLMETHOD uncso2_PkgIndex_Free(PkgIndex_t indexHandle)
    {
        auto pIndex = reinterpret_cast<uc2::PkgIndex*>(indexHandle);
        delete pIndex;
    }

    bool UNCSO2_CALLMETHOD uncso2_PkgIndex_Parse(PkgIndex_t indexHandle)
    {
        if (indexHandle == NULL)
        {
            return false;
        }

        auto pIndex = reinterpret_cast<uc2::PkgIndex*>(indexHandle);

        try
        {
            pIndex->Parse();
            return true;
        }
        catch (const std::exception& e)
        {
            return false;
        }
    }

    uint64_t UNCSO2_CALLMETHOD
    uncso2_PkgIndex_GetFilenamesNum(PkgIndex_t indexHandle)
    {
        if (indexHandle == NULL)
        {
            return 0;
        }

        auto pPkg = reinterpret_cast<uc2::PkgIndex*>(indexHandle);

        try
        {
            return pPkg->GetFilenames().size();
        }
        catch (const std::exception& e)
        {
            return 0;
        }
    }

    const char* const* UNCSO2_CALLMETHOD
    uncso2_PkgIndex_GetFilenames(PkgIndex_t indexHandle)
    {
        if (indexHandle == NULL)
        {
            return 0;
        }

        auto pPkg = reinterpret_cast<uc2::PkgIndex*>(indexHandle);

        try
        {
            return reinterpret_cast<const char* const*>(
                pPkg->GetFilenames().data());
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