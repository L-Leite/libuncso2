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

const std::string PkgFilename = "0a4b4196394ecf251c532f1552ccf3b3.pkg"s;
constexpr const std::uint64_t PackageFileCount = 4;
const std::array<std::string, 4> PackageFileHashes = {
    "42d3b7b74b8feb7f6801930ba58aef6bb85fa2d8a465cffef36c906566cbeeb4",
    "58389be7fbcaa33e143c8e7ed85b7ed73e5d69d095972e9d260a4171ed959224",
    "2968dce6245f50c7ae9803e1b765ff9ed7705a459c4041f4623a46dea24b9873",
    "638f05cce5002f65917125931a07f2541b4fca6819623950f9c306bba18d9ae7",
};

const std::string PkgFilename2 = "d0112b5fb371db812eb586c3d8d19f4f.pkg"s;
constexpr const std::uint64_t PackageFileCount2 = 8;

//
// PKG data END
//
}  // namespace tfo
