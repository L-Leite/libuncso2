#include "keyhashes.hpp"

#include <stdexcept>
#include <string>

#include <hex.h>
#include <md5.h>

namespace uc2
{
std::vector<uint8_t> GeneratePkgIndexKey(
    int iKey, std::string_view szPkgName,
    gsl::span<const uint8_t[4][16]> keyCollectionView)
{
    constexpr const uint32_t iVersion = 2;
    static_assert(sizeof(iVersion) == 4, "iVersion's size must be 4 bytes");

    CryptoPP::Weak::MD5 hash;

    hash.Update(reinterpret_cast<const uint8_t*>(&iVersion), sizeof(iVersion));

    size_t iNameLen = szPkgName.length();
    size_t iKeyIndex = iKey / 2;
    const uint8_t* pKey = (*keyCollectionView.data())[iKeyIndex];

    if (iKey % 2)
    {
        hash.Update(pKey, 16);

        if (iNameLen != 0)
            hash.Update(reinterpret_cast<const uint8_t*>(szPkgName.data()),
                        iNameLen);
    }
    else
    {
        if (iNameLen != 0)
            hash.Update(reinterpret_cast<const uint8_t*>(szPkgName.data()),
                        iNameLen);

        hash.Update(pKey, 16);
    }

    std::vector<uint8_t> key(CryptoPP::Weak::MD5::DIGESTSIZE);
    hash.Final(key.data());

    return key;
}

std::string GeneratePkgFileKey(std::string_view szvPkgName,
                               std::string_view szKey)
{
    if (szvPkgName.empty())
        throw std::invalid_argument("libuncso2: The pkg name cannot be empty");

    CryptoPP::Weak::MD5 hash;

    if (szKey.empty() == false)
        hash.Update(reinterpret_cast<const uint8_t*>(szKey.data()),
                    szKey.length());

    hash.Update(reinterpret_cast<const uint8_t*>(szvPkgName.data()),
                szvPkgName.length());

    std::array<uint8_t, CryptoPP::Weak::MD5::DIGESTSIZE> digestedKey;
    hash.Final(digestedKey.data());

    std::string szOutHash;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(szOutHash), false);
    encoder.Put(digestedKey.data(), digestedKey.size());
    encoder.MessageEnd();

    return szOutHash;
}
}  // namespace uc2