#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

std::pair<bool, std::vector<uint8_t>> ReadFileToBuffer(
    std::string_view filename);

std::string GetDataHash(uint8_t* pData, uint64_t iDataLen);
