/**
 * @file pkgntry.h
 * @author Luís Leite (luis@leite.xyz)
 * @brief Contains file entry data.
 * @version 1.0
 *
 * Contains a class that stores parsed file entries in pkg files.
 */

#pragma once

#include "uc2defs.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Decrypts and returns the file
     *
     * Decrypts the file entry contained in the PkgEntry object.
     * It does NOT allocate new memory, it reuses the buffer given to PkgFile.
     * This function will write the new buffer's address to outBuffer parameter,
     * and write its size to the outSize parameter.
     *
     * @param entryHandle The PkgEntry's object handle.
     * @param outBuffer A pointer to where the new buffer's address will be
     * written to.
     * @param outSize A pointer to where the new buffer's size will be written
     * to.
     * @return true If the data was decrypted successfully.
     * @return false If the function failed to decrypt the data.
     */
    UNCSO2_API bool UNCSO2_CALLMETHOD
    uncso2_PkgEntry_Decrypt(PkgEntry_t entryHandle, void** outBuffer,
                            uint64_t* outSize, uint64_t bytesToDecrypt = 0);

    /**
     * @brief Get the file's path.
     *
     * @param entryHandle The PkgEntry's object handle.
     *
     * @return const char* The file's path.
     */
    UNCSO2_API const char* UNCSO2_CALLMETHOD
    uncso2_PkgEntry_GetPath(PkgEntry_t entryHandle);

    /**
     * @brief Get the file's offset in the pkg file.
     *
     * @param entryHandle The PkgEntry's object handle
     *
     * @return uint64_t The file's offset.
     */
    UNCSO2_API uint64_t UNCSO2_CALLMETHOD
    uncso2_PkgEntry_GetFileOffset(PkgEntry_t entryHandle);

    /**
     * @brief Get the file's encrypted size.
     *
     * @param entryHandle The PkgEntry's object handle
     *
     * @return uint64_t The file's encrypted size.
     */
    UNCSO2_API uint64_t UNCSO2_CALLMETHOD
    uncso2_PkgEntry_GetEncryptedSize(PkgEntry_t entryHandle);

    /**
     * @brief Get the file's decrypted size.
     *
     * @param entryHandle The PkgEntry's object handle
     *
     * @return uint64_t The file's decrypted size.
     */
    UNCSO2_API uint64_t UNCSO2_CALLMETHOD
    uncso2_PkgEntry_GetDecryptedSize(PkgEntry_t entryHandle);

    /**
     * @brief Is this file encrypted?
     *
     * @param entryHandle The PkgEntry's object handle
     *
     * @return true if it's encrypted
     * @return false if it's false
     */
    UNCSO2_API bool UNCSO2_CALLMETHOD
    uncso2_PkgEntry_IsEncrypted(PkgEntry_t entryHandle);
#ifdef __cplusplus
}
#endif
