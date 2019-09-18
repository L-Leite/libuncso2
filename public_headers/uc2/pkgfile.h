/**
 * @file pkgfile.h
 * @author Luís Leite (luis@leite.xyz)
 * @brief Decrypts and parses pkg files.
 * @version 1.0
 *
 * Contains methods that decrypt and parse pkg file's data.
 */

#pragma once

#include "uc2defs.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Construct a new PkgFile object.
     *
     * The file data you passed in the dataBuffer parameter CAN and WILL be
     * modified.
     *
     * It may return NULL if an error occurs.
     *
     * @param filename The PKG file's name.
     * @param dataBuffer The PKG's data.
     * @param dataSize The PKG's data size.
     * @param szEntryKey The PKG data entries' key. The key must be 16 bytes
     * long.
     * @param szDataKey The PKG data's key. The key must be 16 bytes long.
     *
     * @return PkgFile_t A handle to the new PkgFile object.
     */
    UNCSO2_API PkgFile_t UNCSO2_CALLMETHOD uncso2_PkgFile_Create(
        const char* filename, void* dataBuffer, uint64_t dataSize,
        const char* szEntryKey, const char* szDataKey,
        PkgFileOptions_t options = NULL);

    /**
     * @brief Destroys a PkgFile object.
     *
     * Free's the PkgFile object stored in the handle.
     *
     * @param PkgFile_t The PkgFile's object handle to be destroyed.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD uncso2_PkgFile_Free(PkgFile_t pkgHandle);

    /**
     * @brief Gets the PkgFile's file name.
     *
     * @return const char* The PkgFile's file name.
     */
    UNCSO2_API const char* UNCSO2_CALLMETHOD
    uncso2_PkgFile_GetFilename(PkgFile_t pkgHandle);

    /**
     * @brief Sets the header key to use with the PkgFile.
     *
     * @param pkgHandle The PkgFile's object handle.
     * @param szNewEntryKey the new header key.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD
    uncso2_PkgFile_SetEntryKey(PkgFile_t pkgHandle, const char* szNewEntryKey);

    /**
     * @brief Sets the data key to use with the PkgFile.
     *
     * @param pkgHandle The PkgFile's object handle.
     * @param szNewDataKey the new data key.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD
    uncso2_PkgFile_SetDataKey(PkgFile_t pkgHandle, const char* szNewDataKey);

    /**
     * @brief Set the PKG file as a TFO PKG file.
     *
     * Treats the PKG file as if it's from Titanfall Online.
     *
     * @param pkgHandle The PkgFile's object handle.
     * @param bNewState The new TFO PKG file state.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD
    uncso2_PkgFile_SetTfoPkg(PkgFile_t pkgHandle, bool bNewState);

    /**
     * @brief Set a new data buffer to use with the PkgFile.
     *
     * @param pkgHandle The PkgFile's object handle.
     * @param dataBuffer The new data buffer.
     * @param dataSize The new data buffer's size.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD uncso2_PkgFile_SetDataBuffer(
        PkgFile_t pkgHandle, void* dataBuffer, uint64_t dataSize);

    /**
     * @brief Invalidate the stored buffer.
     *
     * @param pkgHandle The PkgFile's object handle.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD
    uncso2_PkgFile_ReleaseDataBuffer(PkgFile_t pkgHandle);

    /**
     * @brief Get the whole header size of a PKG file.
     *
     * Returns the size of the PKG's header and entries.
     *
     * It's enough to provide a buffer with the length returned by the
     * uncso2_PkgFile_GetHeaderSize function. Any more data will be ignored.
     *
     * @param pkgHandle The PkgFile's object handle.
     *
     * @return uint64_t The PKG header's size.
     */
    UNCSO2_API uint64_t UNCSO2_CALLMETHOD
    uncso2_PkgFile_GetFullHeaderSize(PkgFile_t pkgHandle);

    /*
     * @brief Decrypts the PKG file header
     *
     * Decrypts the PKG's file header using the entry key given by the user.
     *
     * @param pkgHandle The PkgFile's object handle.
     */
    UNCSO2_API bool UNCSO2_CALLMETHOD
    uncso2_PkgFile_DecryptHeader(PkgFile_t pkgHandle);

    /**
     * @brief Decrypts and parses pkg files.
     *
     * Decrypt's the pkg file's header, parses it, and reads the file entries in
     * it to a dynamic array of PkgEntry's.
     *
     * You can retrieve the entries through the uncso2_PkgFile_GetEntries
     * method. The entries count can be retrieved from
     * uncso2_PkgFile_GetEntriesNum.
     *
     * @param pkgHandle The PkgFile's object handle.
     *
     * @return true If parsed successfully.
     * @return false If the parsing failed.
     */
    UNCSO2_API bool UNCSO2_CALLMETHOD uncso2_PkgFile_Parse(PkgFile_t pkgHandle);

    /**
     * @brief Get the PKG's number of file entries.
     *
     * @param pkgHandle The PkgFile's object handle.
     *
     * @return uint64_t The number of file entries.
     */
    UNCSO2_API uint64_t UNCSO2_CALLMETHOD
    uncso2_PkgFile_GetEntriesNum(PkgFile_t pkgHandle);

    /**
     * @brief Get the PKG's file entries.
     *
     * @param pkgHandle The PkgFile's object handle.
     *
     * @return PkgEntry_t* The file entries.
     */
    UNCSO2_API PkgEntry_t* UNCSO2_CALLMETHOD
    uncso2_PkgFile_GetEntries(PkgFile_t pkgHandle);

    /**
     * @brief Get the header size of a PKG file.
     *
     * @param bTfoPkg Should the Titanfall Online PKG header's size be
     * retrieved?
     * @return uint64_t The PKG header's size.
     */
    UNCSO2_API uint64_t UNCSO2_CALLMETHOD
    uncso2_PkgFile_GetHeaderSize(bool bTfoPkg);

#ifdef __cplusplus
}
#endif
