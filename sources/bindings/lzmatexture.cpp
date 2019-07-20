#include "lzmatexture.h"
#include "lzmatextureimpl.hpp"

#ifdef __cplusplus
extern "C"
{
    LzmaTexture_t UNCSO2_CALLMETHOD uncso2_LzmaTexture_Create(void* texBuffer,
                                                              uint64_t texSize)
    {
        gsl::span<uint8_t> texView(reinterpret_cast<uint8_t*>(texBuffer),
                                   texSize);

        try
        {
            auto newTex = uc2::LzmaTextureImpl::CreateSpan(texView);
            return reinterpret_cast<LzmaTexture_t>(newTex.release());
        }
        catch (const std::exception& e)
        {
            return NULL;
        }
    }

    void UNCSO2_CALLMETHOD uncso2_LzmaTexture_Free(LzmaTexture_t texHandle)
    {
        auto pTex = reinterpret_cast<uc2::LzmaTexture*>(texHandle);
        delete pTex;
    }

    uint64_t UNCSO2_CALLMETHOD
    uncso2_LzmaTexture_GetOriginalSize(LzmaTexture_t texHandle)
    {
        if (texHandle == NULL)
        {
            return 0;
        }

        auto pTex = reinterpret_cast<uc2::LzmaTexture*>(texHandle);

        try
        {
            return pTex->GetOriginalSize();
        }
        catch (const std::exception& e)
        {
            return 0;
        }
    }

    bool UNCSO2_CALLMETHOD uncso2_LzmaTexture_Decompress(
        LzmaTexture_t texHandle, void* outBuffer, uint64_t outBufferSize)
    {
        if (texHandle == NULL)
        {
            return 0;
        }

        auto pTex = reinterpret_cast<uc2::LzmaTexture*>(texHandle);

        try
        {
            return pTex->Decompress(reinterpret_cast<uint8_t*>(outBuffer),
                                    outBufferSize);
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