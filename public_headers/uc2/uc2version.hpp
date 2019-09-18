/**
 * @file pkgindex.hpp
 * @author Luís Leite (luis@leite.xyz)
 * @brief Contains versioning information about libuncso2.
 * @version 1.0
 */

#pragma once

#include "uc2defs.h"

#include <string_view>

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
class UNCSO2_API Version
{
public:
    /**
     * @brief Get the major version of libuncso2
     *
     * If the version of libuncso2 is "1.2.3", this function will return the
     * number '1'.
     *
     * @returns int The major version of libuncso2
     */
    static int GetMajorVersionNum();

    /**
     * @brief Get the minor version of libuncso2
     *
     * If the version of libuncso2 is "1.2.3", this function will return the
     * number '2'.
     *
     * @returns int The minor version of libuncso2
     */
    static int GetMinorVersionNum();

    /**
     * @brief Get the patch version of libuncso2
     *
     * If the version of libuncso2 is "1.2.3", this function will return the
     * number '3'.
     *
     * @returns int The patch version of libuncso2
     */
    static int GetPatchVersionNum();

    /**
     * @brief Get the version of libuncso2 as a string.
     *
     * It will return a string such as "v1.2.3".
     *
     * @returns std::string_view The patch version of libuncso2
     */
    static std::string_view GetVersionString();
};
}  // namespace uc2
