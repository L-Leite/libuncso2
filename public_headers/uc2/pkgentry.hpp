/**
 * @file pkgntry.hpp
 * @author Luís Leite (luis@leite.xyz)
 * @brief Contains file entry data.
 * @version 1.0
 *
 * Contains a class that stores parsed file entries in pkg files.
 */

#pragma once

#include "uc2defs.h"

#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief The libuncso2's namespace
 */
namespace uc2
{
/**
 * @brief Contains file entry data.
 *
 * Stores parsed data of files from pkg file entries.
 *
 * It's also capable of decrypting the file's data.
 *
 * It uses a custom AES (or Rijndael) 128 CBC class. This class is used by
 * CSO2.
 */
class UNCSO2_API PkgEntry
{
public:
    virtual ~PkgEntry() = default;

    /**
     * @brief Decrypts and returns the file
     *
     * Decrypts the file contained in here and returns a pair of a buffer
     * pointer and the buffer's size.
     * It does NOT allocate new memory, it reuses the buffer given to PkgFile.
     *
     * This method throws exceptions:
     * - It throws std::runtime_error when it tries to decrypt a file larger
     * than its host PKG file.
     *
     * @param iBytesToDecrypt How many file bytes should be decrypted? Default
     * is zero, which means 'decrypt everything'.
     *
     * @return std::pair<uint8_t*, uint64_t> the file's buffer pointer and the
     * buffer's size
     */
    virtual std::pair<uint8_t*, uint64_t> DecryptFile(
        const uint64_t iBytesToDecrypt = 0) = 0;

    /**
     * @brief Get the file's path.
     * @return std::string_view the file's path
     */
    virtual const std::string_view GetFilePath() = 0;

    /**
     * @brief Get the file's offset in the pkg file.
     * @return uint64_t The file's offset.
     */
    virtual uint64_t GetPkgFileOffset() = 0;

    /**
     * @brief Get the file's encrypted size.
     *
     * This usually includes the data's padding.
     * @return uint64_t the file's encrypted size
     */
    virtual uint64_t GetEncryptedSize() = 0;

    /**
     * @brief Get the file's decrypted size
     * @return uint64_t the file's decrypted size
     */
    virtual uint64_t GetDecryptedSize() = 0;

    /**
     * @brief Is this file encrypted?
     * @return true if it's encrypted
     * @return false if it's false
     */
    virtual bool IsEncrypted() = 0;
};
}  // namespace uc2
