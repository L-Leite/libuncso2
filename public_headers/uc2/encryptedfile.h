/**
 * @file encryptedfile.h
 * @author Luís Leite (luis@leite.xyz)
 * @brief Decrypts .e* extension files
 * @version 1.0
 *
 * Contains a class that decrypts files with .e* prefixed extensions (such as
 * 'ecsv' or 'ecfg').
 */

#pragma once

#include "uc2defs.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Construct a new EncryptedFile object.
     *
     * The data referenced in the dataBuffer paramater may and will be modified.
     * Returns NULL if it failed to create a new object.
     *
     * @param filename The encrypted file's name.
     * @param dataBuffer A pointer to the encrypted file's data.
     * @param dataSize The encrypted file's data size.
     * @param keyCollection The key collection to decrypt with. It must have 4
     * keys, and each key must be 16 bytes long-
     *
     * @return EncryptedFile_t The new EncryptedFile's object handle.
     */
    UNCSO2_API EncryptedFile_t UNCSO2_CALLMETHOD uncso2_EncryptedFile_Create(
        const char* filename, void* dataBuffer, uint64_t dataSize,
        const uint8_t (*keyCollection)[4][16]);

    /**
     * @brief Destroys an EncryptedFile object.
     *
     * Free's the EncryptedFile object stored in the handle.
     *
     * @param fileHandle The EncryptedFile's object handle to be destroyed.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD
    uncso2_EncryptedFile_Free(EncryptedFile_t fileHandle);

    /**
     * @brief Decrypts the file
     *
     * Decrypts the file through the same decryption method in PkgIndex.
     * It reuses the buffer provided in the factory method
     * uncso2_EncryptedFile_Create to store the decrypted data.
     * The method will write the resulting buffer to the outBuffer parameter,
     * and its size to the outSize parameter.
     *
     * @param fileHandle The EncryptedFile's object handle.
     * @param outBuffer A pointer to where the resulting data buffer will be
     * written.
     * @param outSize A pointer to where the resulting data buffer's length will
     * be written.
     * @return true If the data was decrypted successfully.
     * @return false If there was an error decrypting the data.
     */
    UNCSO2_API bool UNCSO2_CALLMETHOD uncso2_EncryptedFile_Decrypt(
        EncryptedFile_t fileHandle, void** outBuffer, uint64_t* outSize);
#ifdef __cplusplus
}
#endif
