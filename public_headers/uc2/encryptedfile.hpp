/**
 * @file encryptedfile.hpp
 * @author Luís Leite (luis@leite.xyz)
 * @brief Decrypts .e* extension files
 * @version 1.0
 *
 * Contains a class that decrypts files with .e* prefixed extensions (such as
 * 'ecsv' or 'ecfg').
 */

#pragma once

#include "uc2defs.h"

#include <stdint.h>
#include <array>
#include <memory>
#include <string_view>
#include <vector>

/**
 * @brief The libuncso2's namespace.
 */
namespace uc2
{
/**
 * @brief Decrypts .e* extension files.
 *
 * The file extensions that prefixes start with an 'e' (such as 'ecsv' or
 * 'ecfg') are encrypted through the same methods pkg indexes are.
 *
 * This class handles its decryption logic.
 */
class UNCSO2_API EncryptedFile
{
public:
    using ptr_t = std::unique_ptr<EncryptedFile>; /*!< The pointer type of
                                                     EncryptedFile */

    virtual ~EncryptedFile() = default;

    /**
     * @brief Decrypts the file.
     *
     * Decrypts the file through the same decryption method in PkgIndex.
     *
     * @return std::pair<uint8_t*, size_t> A pair with the buffer pointer and
     * the buffer's length.
     */
    virtual std::pair<uint8_t*, size_t> Decrypt() = 0;

    /**
     * @brief Construct a new EncryptedFile object.
     *
     * The data referenced in the fileData paramater may and will be modified.
     *
     * This method throws exceptions:
     * - It throws std::invalid_argument when the file's header is invalid.
     *
     * @param fileName The encrypted file's name.
     * @param fileData The encrypted file's data.
     * @param keyCollection The key collection to decrypt with. It must have 4
     * keys, and each key must be 16 bytes long-
     *
     * @return ptr_t the new EncryptedFile object.
     */
    static ptr_t Create(std::string_view fileName,
                        std::vector<uint8_t>& fileData,
                        const uint8_t (&keyCollection)[4][16]);
};
}  // namespace uc2
