#include "uc2version.h"
#include "uc2version.hpp"

#ifdef __cplusplus
extern "C"
{
    int UNCSO2_CALLMETHOD uncso2_GetMajorVersionNum()
    {
        return uc2::Version::GetMajorVersionNum();
    }

    int UNCSO2_CALLMETHOD uncso2_GetMinorVersionNum()
    {
        return uc2::Version::GetMinorVersionNum();
    }

    int UNCSO2_CALLMETHOD uncso2_GetPatchVersionNum()
    {
        return uc2::Version::GetPatchVersionNum();
    }

    const char* UNCSO2_CALLMETHOD uncso2_GetVersionString()
    {
        return uc2::Version::GetVersionString().data();
    }
#endif

#ifdef __cplusplus
}
#endif