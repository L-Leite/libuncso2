/**
 * @file uc2version.h
 * @author Luís Leite (luis@leite.xyz)
 * @brief Contains versioning information about libuncso2.
 * @version 1.0
 */

#pragma once

#include "uc2defs.h"

#ifdef __cplusplus
extern "C"
{
#endif
    /**
     * @brief Get the major version of libuncso2
     *
     * If the version of libuncso2 is "1.2.3", this function will return the
     * number '1'.
     *
     * @returns int The major version of libuncso2
     */
    UNCSO2_API int UNCSO2_CALLMETHOD uncso2_GetMajorVersionNum();

    /**
     * @brief Get the minor version of libuncso2
     *
     * If the version of libuncso2 is "1.2.3", this function will return the
     * number '2'.
     *
     * @returns int The minor version of libuncso2
     */
    UNCSO2_API int UNCSO2_CALLMETHOD uncso2_GetMinorVersionNum();

    /**
     * @brief Get the patch version of libuncso2
     *
     * If the version of libuncso2 is "1.2.3", this function will return the
     * number '3'.
     *
     * @returns int The patch version of libuncso2
     */
    UNCSO2_API int UNCSO2_CALLMETHOD uncso2_GetPatchVersionNum();

    /**
     * @brief Get the version of libuncso2 as a string.
     *
     * It will return a string such as "v1.2.3".
     *
     * @returns const char* The patch version of libuncso2
     */
    UNCSO2_API const char* UNCSO2_CALLMETHOD uncso2_GetVersionString();
#ifdef __cplusplus
}
#endif
