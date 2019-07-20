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

#include <stdint.h>
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
 *
 * It uses a custom AES (or Rijndael) 128 CBC class. This class is used by
 * CSO2.
 *
 * TODO: Is it possible to use OpenSSL to decrypt the pkg data?
 */
class UNCSO2_API PkgFile
{
public:
    using ptr_t = std::unique_ptr<PkgFile>; /*!< The pointer type of PkgFile */
    using entryptr_t =
        std::unique_ptr<PkgEntry>; /*!< The pointer type of PkgEntry */

    virtual ~PkgFile() = default;

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
     * This method throws exceptions:
     * - It throws std::range_error if the PKG's data is too small.
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
    static ptr_t Create(std::string_view szvFilename,
                        std::vector<uint8_t>& fileData,
                        std::string_view szvEntryKey,
                        std::string_view szvDataKey,
                        PkgFileOptions* options = nullptr);
};
}  // namespace uc2
