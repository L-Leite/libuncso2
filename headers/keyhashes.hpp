#include <cstdint>
#include <array>
#include <gsl/gsl>
#include <string_view>
#include <vector>

namespace uc2
{
std::vector<uint8_t> GeneratePkgIndexKey(
    int iKey, std::string_view szPkgName,
    gsl::span<const uint8_t[4][16]> keyCollectionView);

std::string GeneratePkgFileKey(std::string_view szvPkgName,
                               std::string_view szKey);
}  // namespace uc2