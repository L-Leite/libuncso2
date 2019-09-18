/**
 * @file pkgfile.hpp
 * @author Luís Leite (luis@leite.xyz)
 * @brief Decrypts and parses pkg files.
 * @version 1.0
 *
 * Contains a class that contains decrypted and parsed pkg file's data.
 */

#pragma once

#include "uc2defs.h"

#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

#include "pkgfileoptions.hpp"

/**
 * @brief The libuncso2's namespace
 */
namespace uc2
{
class PkgEntry;
class PkgFileOptions;

/**
 * @brief Decrypts and parses pkg files.
 *
 * This class contains logic to decrypt and parse pkg files.
 *
 * It decrypts and parses pkg file's headers, and stores the pkg file's entries.
 *
 * The pkg file's entries are stored in PkgEntry classes.
 */
class UNCSO2_API PkgFile
{
public:
    using ptr_t = std::unique_ptr<PkgFile>; /*!< The pointer type of PkgFile */
    using entryptr_t =
        std::unique_ptr<PkgEntry>; /*!< The pointer type of PkgEntry */

    virtual ~PkgFile() = default;

    /**
     * @brief Gets the PkgFile's file name.
     *
     * @return std::string_view The PkgFile's file name.
     */
    virtual std::string_view GetFilename() = 0;

    /**
     * @brief Sets the header key to use with the PkgFile.
     *
     * @param szNewEntryKey the new header key.
     */
    virtual void SetEntryKey(std::string szNewEntryKey) = 0;

    /**
     * @brief Sets the data key to use with the PkgFile.
     *
     * @param szNewDataKey the new data key.
     */
    virtual void SetDataKey(std::string szNewDataKey) = 0;

    /**
     * @brief Set the PKG file as a TFO PKG file.
     *
     * Treats the PKG file as if it's from Titanfall Online.
     *
     * @param bNewState The new TFO PKG file state.
     */
    virtual void SetTfoPkg(bool bNewState) = 0;

    /**
     * @brief Set a new data buffer to use with the PkgFile.
     *
     * @param newFileData The new data buffer.
     */
    virtual void SetDataBuffer(std::vector<uint8_t>& newFileData) = 0;

    /**
     * @brief Invalidate the stored buffer.
     */
    virtual void ReleaseDataBuffer() = 0;

    /**
     * @brief Get the whole header size of a PKG file.
     *
     * Returns the size of the PKG's header and entries.
     *
     * It's enough to provide a buffer with the length returned by the
     * GetHeaderSize method. Any more data will be ignored.
     *
     * @return uint64_t The PKG header's size.
     */
    virtual uint64_t GetFullHeaderSize() = 0;

    /**
     * @brief Get the PKG's MD5 hash string.
     *
     * At the moment the PKG is not validated with the MD5 hash.
     *
     * @return std::string_view The PKG's MD5 hash string-
     */
    virtual std::string_view GetMd5Hash() = 0;

    /**
     *
     * @brief Decrypts the PKG file header
     *
     * Decrypts the PKG's file header using the entry key given by the user.
     *
     * This method throws exceptions:
     * - It throws std::runtime_error if the file data, data key, or entry key
     * provided are empty.
     *
     * @return true If the header was decrypted successfully or is decrypted
     * already.
     * @return false If the header could not be decrypted.
     */
    virtual bool DecryptHeader() = 0;

    /**
     * @brief Decrypts and parses pkg files.
     *
     * Decrypt's the pkg file's header, parses it, and reads the file entries in
     * it to a dynamic array of PkgEntry's.
     *
     * You can retrieve the entries through the GetEntries() method.
     *
     * This method throws exceptions:
     * - It throws std::invalid_argument if the PKG entry's size is bigger than
     * the PKG itself.
     * - It throws std::range_error if the PKG's data is too small.
     */
    virtual void Parse() = 0;

    /**
     * @brief Get the file entries.
     *
     * Retrieves the parsed pkg's file entries.
     *
     * @return std::vector<entryptr_t>& The file entries.
     */
    virtual std::vector<entryptr_t>& GetEntries() = 0;

    /**
     * @brief Construct a new PkgFile object.
     *
     * The file data you passed in the fileData parameter CAN and WILL be
     * modified.
     *
     * The client is responsible by the lifetime of the std::string_view typed
     * parameters.
     *
     * @param szvFilename The pkg file's name
     * @param fileData The pkg's data
     * @param szvEntryKey The pkg data entries' key. The key must be 16 bytes
     * long.
     * @param szvDataKey The pkg data's key. The key must be 16 bytes long.
     * @param options The options to use in this PkgFile, it may be null.
     *
     * @return ptr_t the new PkgFile object
     */
    static ptr_t Create(std::string szFilename, std::vector<uint8_t>& fileData,
                        std::string szEntryKey = {}, std::string szDataKey = {},
                        PkgFileOptions* options = nullptr);

    /**
     * @brief Get the header size of a PKG file.
     *
     * @param bTfoPkg Should the Titanfall Online PKG header's size be
     * retrieved?
     * @return uint64_t The PKG header's size.
     */
    static uint64_t GetHeaderSize(bool bTfoPkg);
};
}  // namespace uc2
