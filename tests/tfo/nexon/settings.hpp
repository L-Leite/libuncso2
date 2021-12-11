#pragma once

#include <array>
#include <string>

using namespace std::literals::string_literals;

namespace tfo
{
//
// Index data START
//
const std::string IndexFilename = "index_tfo.pkg"s;

const std::string IndexRealFilename = "1b87c6b551e518d11114ee21b7645a47.pkg"s;

constexpr const std::uint64_t IndexFileCount = 1077;

constexpr const std::uint8_t IndexKeyCollection[4][16] = {
    { 0x49, 0x17, 0x7A, 0x74, 0xA3, 0xE4, 0x26, 0x48, 0xBF, 0x07, 0x8F, 0x21,
      0xC4, 0x6C, 0x7A, 0xEE },
    { 0x98, 0xDF, 0x70, 0xE2, 0xFB, 0xAE, 0x88, 0x46, 0xA1, 0x7C, 0x99, 0xE3,
      0x52, 0x49, 0x9A, 0x21 },
    { 0x12, 0xEB, 0xF8, 0xEE, 0xD0, 0x6C, 0x88, 0x4B, 0x8A, 0x49, 0x88, 0x76,
      0x7C, 0x4E, 0x1E, 0xB7 },
    { 0x9A, 0xA6, 0xC7, 0x59, 0x18, 0xEA, 0xD0, 0x44, 0x83, 0xA3, 0x3A, 0x3E,
      0xCE, 0xAF, 0x6F, 0x68 }
};
//
// Index data END
//

//
// PKG data START
//

const std::string PackageEntryKey = "lkgui781kl789sd!@#%89&^sd"s;
const std::string PackageFileKey = "^9gErg2Sx7bnk7@#sdfjnh@"s;

const std::vector<std::pair<std::string, std::vector<std::string>>> Packages = {
    {
        "0a4b4196394ecf251c532f1552ccf3b3.pkg",
        {
            "cab6520af0e54b17b46a9ae45611c339e64e50e06f341dd834464acc9689af15",
            "31d262620204566d8c3f7bf40f637d6229c2b15b1dd5abee1f784d7b5fba6c97",
            "c013887bc3e6e16e4ce84d6c674faea8e70e27b2b0d2864e534f78c88b2be270",
            "c9173ac086723d08025380964c38e905a93116eb77ea7d6d3edb24e07bc81d4b",
        }
    },
    {
       "d0112b5fb371db812eb586c3d8d19f4f.pkg",
        {
            "c32759a871bc14ce2f84381a63dec7895b4376a9d69ef65421a770cae9ab34e4",
            "5a2c571f3fec0c83075a97a7f6f8bc52864e9fc2c5576d9db77fd3d25c73950b",
            "437510ea732d3d10befc8940cbb2e38777271fdb51e23c5354843f4625a4f99d",
            "4355f6960122aac15ee3f069ab2da06783cf4e17a132fef6eac36309d3be0bc7",
            "55562fbc475b77283260950ca5810571d27096bc5d5f89388e2736ce7dd21bb3",
            "7c2ed35e2ce03c61e199fb7842759605b5443262d6319ce3e1cb71ce28e00bae",
            "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
            "443a3b4d621cbba7429118d82a001e513327d8831a76414e3b47052cdf2888a5",
        }
    },
};

//
// PKG data END
//
}  // namespace tfo
