/**
 * @file pkgfileoptions.h
 * @author Luís Leite (luis@leite.xyz)
 * @brief Options to use with PkgFile
 * @version 1.0
 *
 * It manages options to use with the PkgFile class.
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
     * @return PkgFile_t A handle to the new PkgFileOptions object.
     */
    UNCSO2_API PkgFileOptions_t UNCSO2_CALLMETHOD
    uncso2_PkgFileOptions_Create();

    /**
     * @brief Destroys a PkgFileOptions object.
     *
     * Free's the PkgFileOptions object stored in the handle.
     *
     * @param PkgFileOptions_t The PkgFileOptions's object handle to be
     * destroyed.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD
    uncso2_PkgFileOptions_Free(PkgFileOptions_t optionsHandle);

    /**
     * @brief Set if the PKG is from Titanfall Online.
     *
     * To manage PKGs from Titanfall Online, this method must be called with the
     * state parameter as 'true'.
     *
     * Titanfall Online uses a different header structure from Counter-Strike
     * Online 2.
     *
     * @param optionsHandle The PkgFileOptions's object handle.
     * @param state The new 'is Titanfall Online PKG' state.
     */
    UNCSO2_API void UNCSO2_CALLMETHOD
    uncso2_PkgFileOptions_SetTfoPkg(PkgFileOptions_t optionsHandle, bool state);

    /**
     * @brief Is the Titanfall Online PKG option enabled?
     *
     * @param optionsHandle The PkgFile's object handle.
     *
     * @return true If the option is enabled.
     * @return false If the option is disabled.
     */
    UNCSO2_API bool UNCSO2_CALLMETHOD
    uncso2_PkgFileOptions_IsTfoPkg(PkgFileOptions_t optionsHandle);

#ifdef __cplusplus
}
#endif
