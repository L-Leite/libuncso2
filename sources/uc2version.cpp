#include "uc2version.hpp"

#include <string>

using namespace std::string_view_literals;

namespace uc2
{
constexpr const int MAJOR_VERSION = 1;
constexpr const int MINOR_VERSION = 1;
constexpr const int PATCH_VERSION = 0;
constexpr const std::string_view VERSION_STRING = "1.1.0"sv;

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