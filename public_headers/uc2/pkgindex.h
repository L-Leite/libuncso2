/**
 * @file pkgindex.h
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
     * @brief Construct a new PkgIndex object.
     *
     * The file data you pass to the method CAN and WILL be modified.
     *
     * It may return NULL if an error occurs.
     *
     * @param filename The pkg index file's name.
     * @param dataBuffer A pointer to the index's data.
     * @param dataSize The index's data size.
     * @param keyCollection The key collection to decrypt with. It must have 4
     * keys, and each key must be 16 bytes long.
     *
     * @return PkgIndex_t A handle to the new PkgIndex object.
     */
    UNCSO2_API PkgIndex_t UNCSO2_CALLMETHOD uncso2_PkgIndex_Create(
        const char* filename, void* dataBuffer, uint64_t dataSize,
        const uint8_t (*keyCollection)[4][16]);

    /**
     * @brief Destroys a PkgIndex object.
     *
     * Free's the PkgIndex object stored in the handle.
     *
     * @param indexHandle The PkgIndex's object handle to be destroyed.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD
    uncso2_PkgIndex_Free(PkgIndex_t indexHandle);

    /**
     * @brief Set the key collection to be used with the index file.
     *
     * @param indexHandle The PkgIndex's object handle.
     * @param keyCollection The new key collection to decrypt with. It must have
     * 4 keys, and each key must be 16 bytes long.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD uncso2_PkgIndex_SetKeyCollection(
        PkgIndex_t indexHandle, const uint8_t (*keyCollection)[4][16]);

    /**
     * @brief Checks if the index's header is valid.
     *
     * This method must be called before Parse.
     *
     * @param indexHandle The PkgIndex's object handle.
     *
     * @return true If the index's header was read successfully.
     * @return false If there was an error reading the header.
     */
    UNCSO2_API bool UNCSO2_CALLMETHOD
    uncso2_PkgIndex_ValidateHeader(PkgIndex_t indexHandle);

    /**
     * @brief Decrypts and parses index files.
     *
     * Decrypts the index's header, parses it, and stores every file name entry
     * to a dynamic vector. The file names can be retrieved with the
     * uncso2_PkgIndex_GetFilenames function.
     * To get the number of file name entries, use the
     * uncso2_PkgIndex_GetFilenamesNum function.
     *
     * @param indexHandle The PkgIndex's object handle.
     *
     * @return true If the index was parsed successfully.
     * @return false If there was an error parsing the index.
     */
    UNCSO2_API bool UNCSO2_CALLMETHOD
    uncso2_PkgIndex_Parse(PkgIndex_t indexHandle);

    /**
     * @brief Returns the number of parsed file name entries.
     *
     * @param indexHandle The PkgIndex's object handle.
     *
     * @return uint64_t The number of parsed file name entries.
     */
    UNCSO2_API uint64_t UNCSO2_CALLMETHOD
    uncso2_PkgIndex_GetFilenamesNum(PkgIndex_t indexHandle);

    /**
     * @brief Returns the parsed file name entries.
     *
     * @param indexHandle The PkgIndex's object handle.
     *
     * @return const char* const* The parsed file name entries.
     */
    UNCSO2_API const char* const* UNCSO2_CALLMETHOD
    uncso2_PkgIndex_GetFilenames(PkgIndex_t indexHandle);
#ifdef __cplusplus
}
#endif
