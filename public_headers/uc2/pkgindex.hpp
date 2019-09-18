/**
 * @file pkgindex.hpp
 * @author Luís Leite (luis@leite.xyz)
 * @brief Decrypts and parses pkg index files.
 * @version 1.0
 *
 * Contains a class that contains decrypted and parsed pkg index's data.
 */

#pragma once

#include "uc2defs.h"

#include <array>
#include <cstdint>
#include <memory>
#include <string_view>
#include <vector>

/**
 * @brief The libuncso2's namespace
 */
namespace uc2
{
/**
 * @brief Decrypts and parses pkg index files.
 *
 * This class contains logic to parse and decrypt pkg index files.
 *
 * The index files contain a list of a game's file names.
 *
 * It currently supports AES 128 CBC, DES 128 CBC and Blowfish as decryption
 * ciphers.
 */
class UNCSO2_API PkgIndex
{
public:
    using ptr_t =
        std::unique_ptr<PkgIndex>; /*!< The pointer type of PkgIndex */

    virtual ~PkgIndex() = default;

    /**
     * @brief Set the key collection to be used with the index file.
     *
     * @param keyCollection A reference to a list of keys to decrypt the pkg.
     */
    virtual void SetKeyCollection(const uint8_t (*keyCollection)[4][16]) = 0;

    /**
     * @brief Checks if the index's header is valid.
     *
     * This method must be called before Parse.
     *
     * This method throws exceptions:
     * - It throws std::range_error if the index's data is too small.
     * - It throws std::runtime_error if the index's version is unsupported
     * (different from version 2).
     * - It throws std::length_error If the index's size does not match the
     * original's file size.
     */
    virtual void ValidateHeader() = 0;

    /**
     * @brief Decrypts and parses index files.
     *
     * Decrypts the index's header, parses it, and stores every file name entry
     * to a dynamic vector. The file names can be retrieved with the
     * GetFilenames() method.
     *
     * This method throws exceptions:
     * - It throws std::runtime_error if the method failed to decrypt the
     * index's data - this should be caused by a bad key; or if the header was
     * not validated previously by calling the ValidateHeader method.
     *
     * @returns the buffer's decrypted size
     */
    virtual uint64_t Parse() = 0;

    /**
     * @brief Gets the index's file names
     *
     * Retrieves the file names parsed from the index file.
     *
     * @return const std::vector<std::string_view>& the index's file names
     */
    virtual const std::vector<std::string_view>& GetFilenames() = 0;

    /**
     * @brief Construct a new PkgIndex object.
     *
     * The file data you pass to the method CAN and WILL be modified.
     *
     * @param indexFilename The pkg index file's name
     * @param fileData The pkg index's data
     * @param keyCollection A pointer to a list of keys to decrypt the pkg
     * index's data. It must have 4 keys, and each key must be 16 bytes long.
     *
     * @return ptr_t the new PkgIndex object
     */
    static ptr_t Create(std::string_view indexFilename,
                        std::vector<uint8_t>& fileData,
                        const uint8_t (*keyCollection)[4][16] = nullptr);
};
}  // namespace uc2
