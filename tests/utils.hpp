#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

std::pair<bool, std::vector<std::uint8_t>> ReadFileToBuffer(
    std::string_view filename);

std::string GetDataHash(std::uint8_t* pData, std::uint64_t iDataLen);
