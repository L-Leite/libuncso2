/**
 * @file lzmatexture.h
 * @author Luís Leite (luis@leite.xyz)
 * @brief Decompresses LZMA'd VTFs
 * @version 1.0
 *
 * Contains a class that decompresses Valve Texture Files that were compressed
 * with LZMA.
 */

#pragma once

#include "uc2defs.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Construct a new LzmaTexture object.
     *
     * The texture's data input passed in texBuffer is not modified.
     *
     * It may return NULL if an error occurs.
     *
     * @param texBuffer A pointer to the texture's data.
     * @param texSize The texture's data size.
     *
     * @return LzmaTexture_t The new LzmaTexture's object
     * handle.
     */
    UNCSO2_API LzmaTexture_t UNCSO2_CALLMETHOD
    uncso2_LzmaTexture_Create(void* texBuffer, uint64_t texSize);

    /**
     * @brief Destroys a LzmaTexture object.
     *
     * Free's the LzmaTexture object stored in the handle.
     *
     * @param texHandle The LzmaTexture's object handle to be destroyed.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD
    uncso2_LzmaTexture_Free(LzmaTexture_t texHandle);

    /**
     * @brief Retrieves the texture's real size.
     *
     * Retrieves the real texture's size from its compressed LZMA header.
     *
     * @param texHandle The LzmaTexture's object handle.
     * @return uint64_t The texture's real size.
     */
    UNCSO2_API uint64_t UNCSO2_CALLMETHOD
    uncso2_LzmaTexture_GetOriginalSize(LzmaTexture_t texHandle);

    /**
     * @brief Does the buffer data's have an LZMA texture header?
     *
     * Validates the data's size and checks the header's magic signature.
     *
     * @param pData The buffer data.
     * @param iDataSize THe buffer's size.
     * @return true If the buffer data has an LZMA texture header.
     * @return false If the buffer data does NOT have an LZMA texture header.
     */
    UNCSO2_API bool uncso2_LzmaTexture_IsLzmaTexture(void* pData,
                                                     const uint64_t iDataSize);

    /**
     * @brief Gets the size of a compressed texture's header.
     *
     * @return uint64_t The size of a compressed texture's header.
     */
    UNCSO2_API uint64_t uncso2_LzmaTexture_GetHeaderSize();

    /**
     * @brief Decompresses the texture.
     *
     * Decompresses the texture using LZMA.
     * The user must allocate and provide the outBuffer.
     * The buffer must have the size returned in the method
     * uncso2_LzmaTexture_GetOriginalSize.
     * The outBufferSize must be the same as the result of the method
     * GetOriginalSize.
     *
     * @param texHandle The LzmaTexture's object handle.
     * @param outBuffer The user's allocated out buffer.
     * @param outBufferSize The out buffer's size.
     * @return true if it was decompressed successfully.
     * @return false if it failed to decompress.
     */
    UNCSO2_API bool UNCSO2_CALLMETHOD uncso2_LzmaTexture_Decompress(
        LzmaTexture_t texHandle, void* outBuffer, uint64_t outBufferSize);
#ifdef __cplusplus
}
#endif
