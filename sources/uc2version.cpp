#include "uc2version.hpp"

#include <string_view>

#include "lib_version.hpp"

namespace uc2
{
int Version::GetMajorVersionNum()
{
    return MAJOR_VERSION;
}

int Version::GetMinorVersionNum()
{
    return MINOR_VERSION;
}

int Version::GetPatchVersionNum()
{
    return PATCH_VERSION;
}

std::string_view Version::GetVersionString()
{
    return VERSION_STRING;
}
}  // namespace uc2