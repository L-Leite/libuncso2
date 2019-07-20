/**
 * @file pkgfileoptions.hpp
 * @author Luís Leite (luis@leite.xyz)
 * @brief Options to use with PkgFile
 * @version 1.0
 *
 * It manages options to use with the PkgFile class.
 */

#pragma once

#include "uc2defs.h"

#include <memory>

/**
 * @brief The libuncso2's namespace
 */
namespace uc2
{
/**
 * @brief Options to use with PkgFile
 *
 */
class PkgFileOptions
{
public:
    using ptr_t = std::unique_ptr<PkgFileOptions>; /*!< The pointer type of
                                                      PkgFileOptions */

    virtual ~PkgFileOptions() = default;

    /**
     * @brief Set if the PKG is from Titanfall Online.
     *
     * To manage PKGs from Titanfall Online, this method must be called with the
     * state parameter as 'true'.
     *
     * Titanfall Online uses a different header structure from Counter-Strike
     * Online 2.
     *
     * @param state The new 'is Titanfall Online PKG' state.
     */
    virtual void SetTfoPkg(bool state) = 0;

    /**
     * @brief Is the Titanfall Online PKG option enabled?
     *
     * @return true If the option is enabled.
     * @return false If the option is disabled.
     */
    virtual bool IsTfoPkg() = 0;

    /**
     * @brief Construct a new PkgFileOptions object.
     *
     * It initializes its members as disabled by default.
     *
     * @return ptr_t the new PkgFileOptions object.
     */
    static ptr_t Create();
};
}  // namespace uc2
