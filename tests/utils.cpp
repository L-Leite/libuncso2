#include "utils.hpp"

#include <array>
#include <fstream>

#include <hex.h>
#include <sha.h>

std::pair<bool, std::vector<std::uint8_t>> ReadFileToBuffer(
    std::string_view filename)
{
    std::ifstream is(filename.data(), std::ios::binary | std::ios::ate);

    if (is.is_open() == false)
    {
        return { false, std::vector<std::uint8_t>() };
    }

    auto iFileSize = is.tellg();
    std::vector<std::uint8_t> res(iFileSize);

    is.seekg(std::ios::beg);
    is.read(reinterpret_cast<char*>(res.data()), iFileSize);

    return { true, std::move(res) };
}

std::string GetDataHash(std::uint8_t* pData, std::uint64_t iDataLen)
{
    std::array<std::uint8_t, CryptoPP::SHA256::DIGESTSIZE> buf;
    CryptoPP::SHA256().CalculateDigest(buf.data(), pData, iDataLen);

    std::string szOutHash;

    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(szOutHash), false);
    encoder.Put(buf.data(), buf.size());
    encoder.MessageEnd();

    return szOutHash;
}
