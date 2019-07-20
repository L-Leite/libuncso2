#pragma once

#include <array>
#include <string_view>

using namespace std::literals::string_view_literals;

namespace cso2
{
enum class Provider
{
    Nexon = 0,
    Tiancity,
    Beancity,
    NexonJP,
};

constexpr const uint64_t NUM_PROVIDERS = 4;

//
// Index data START
//
constexpr const std::array<std::string_view, 4> IndexFilenames = {
    "index_nexon.pkg"sv,     // Nexon
    "index_tiancity.pkg"sv,  // Tiancity
    "index_beancity.pkg"sv,  // Beancity
    "index_nexonjp.pkg"sv    // NexonJP
};

constexpr const std::array<std::string_view, 4> IndexRealFilenames = {
    "1b87c6b551e518d11114ee21b7645a47.pkg"sv,  // Nexon
    "1b87c6b551e518d11114ee21b7645a47.pkg"sv,  // Tiancity
    "1b87c6b551e518d11114ee21b7645a47.pkg"sv,  // Beancity
    "1b87c6b551e518d11114ee21b7645a47.pkg"sv   // NexonJP
};

constexpr const std::array<uint64_t, 4> IndexFileCounts = {
    2091,  // Nexon
    2087,  // Tiancity
    2045,  // Beancity
    1634   // NexonJP
};

constexpr const uint8_t IndexKeyCollections[5][4][16] = {
    {
        { 0x9A, 0xA6, 0xC7, 0x59, 0x18, 0xEA, 0xD0, 0x44, 0x83, 0xA3, 0x3A,
          0x3E, 0xCE, 0xAF, 0x6F, 0x68 },
        { 0xB6, 0xBA, 0x15, 0xC7, 0x77, 0x9D, 0x9C, 0x49, 0x84, 0x62, 0x2A,
          0x9A, 0x8A, 0x61, 0x84, 0xA6 },
        { 0x68, 0x55, 0x24, 0x24, 0x2B, 0xCB, 0x88, 0x4B, 0xA7, 0xA6, 0xD2,
          0xC7, 0x94, 0xED, 0xE8, 0xD3 },
        { 0x36, 0x24, 0xD6, 0x8C, 0x6C, 0xB8, 0xE1, 0x4A, 0xB1, 0x82, 0xC0,
          0xA3, 0xDC, 0xE4, 0x16, 0xC8 },
    },  // Nexon
    {
        { 0x9A, 0xA6, 0xC7, 0x59, 0x18, 0xEA, 0xD0, 0x44, 0x83, 0xA3, 0x3A,
          0x3E, 0xCE, 0xAF, 0x6F, 0x68 },
        { 0xB6, 0xBA, 0x15, 0xC7, 0x77, 0x9D, 0x9C, 0x49, 0x84, 0x62, 0x2A,
          0x9A, 0x8A, 0x61, 0x84, 0xA6 },
        { 0x68, 0x55, 0x24, 0x24, 0x2B, 0xCB, 0x88, 0x4B, 0xA7, 0xA6, 0xD2,
          0xC7, 0x94, 0xED, 0xE8, 0xD3 },
        { 0x36, 0x24, 0xD6, 0x8C, 0x6C, 0xB8, 0xE1, 0x4A, 0xB1, 0x82, 0xC0,
          0xA3, 0xDC, 0xE4, 0x16, 0xC8 },
    },  // Tiancity
    {
        { 0x9A, 0xA6, 0xC7, 0x59, 0x18, 0xEA, 0xD0, 0x44, 0x83, 0xA3, 0x3A,
          0x3E, 0xCE, 0xAF, 0x6F, 0x68 },
        { 0xB6, 0xBA, 0x15, 0xC7, 0x77, 0x9D, 0x9C, 0x49, 0x84, 0x62, 0x2A,
          0x9A, 0x8A, 0x61, 0x84, 0xA6 },
        { 0x68, 0x55, 0x24, 0x24, 0x2B, 0xCB, 0x88, 0x4B, 0xA7, 0xA6, 0xD2,
          0xC7, 0x94, 0xED, 0xE8, 0xD3 },
        { 0x36, 0x24, 0xD6, 0x8C, 0x6C, 0xB8, 0xE1, 0x4A, 0xB1, 0x82, 0xC0,
          0xA3, 0xDC, 0xE4, 0x16, 0xC8 },
    },  // Beancity
    {
        { 0x9A, 0xA6, 0xC7, 0x59, 0x18, 0xEA, 0xD0, 0x44, 0x83, 0xA3, 0x3A,
          0x3E, 0xCE, 0xAF, 0x6F, 0x68 },
        { 0xB6, 0xBA, 0x15, 0xC7, 0x77, 0x9D, 0x9C, 0x49, 0x84, 0x62, 0x2A,
          0x9A, 0x8A, 0x61, 0x84, 0xA6 },
        { 0x68, 0x55, 0x24, 0x24, 0x2B, 0xCB, 0x88, 0x4B, 0xA7, 0xA6, 0xD2,
          0xC7, 0x94, 0xED, 0xE8, 0xD3 },
        { 0x36, 0x24, 0xD6, 0x8C, 0x6C, 0xB8, 0xE1, 0x4A, 0xB1, 0x82, 0xC0,
          0xA3, 0xDC, 0xE4, 0x16, 0xC8 },
    },  // NexonJP
    {
        { 0x49, 0x17, 0x7A, 0x74, 0xA3, 0xE4, 0x26, 0x48, 0xBF, 0x07, 0x8F,
          0x21, 0xC4, 0x6C, 0x7A, 0xEE },
        { 0x98, 0xDF, 0x70, 0xE2, 0xFB, 0xAE, 0x88, 0x46, 0xA1, 0x7C, 0x99,
          0xE3, 0x52, 0x49, 0x9A, 0x21 },
        { 0x12, 0xEB, 0xF8, 0xEE, 0xD0, 0x6C, 0x88, 0x4B, 0x8A, 0x49, 0x88,
          0x76, 0x7C, 0x4E, 0x1E, 0xB7 },
        { 0x9A, 0xA6, 0xC7, 0x59, 0x18, 0xEA, 0xD0, 0x44, 0x83, 0xA3, 0x3A,
          0x3E, 0xCE, 0xAF, 0x6F, 0x68 },
    }  // TfoNexon
};
//
// Index data END
//

//
// PKG data START
//
constexpr const std::array<std::string_view, 5> PkgFilenames = {
    "e8a0dcce7c40cf3549ee7e0093ae8041.pkg"sv,  // Nexon
    "0a2f771750e8c054042f6a3e50e17227.pkg"sv,  // Tiancity
    "0a6c83f37678b86bd78d2367c457e742.pkg"sv,  // Beancity
    "0a4ce29006cca39147b4ea2b3c5e5c3e.pkg"sv,  // NexonJP
    "0a4b4196394ecf251c532f1552ccf3b3.pkg"sv   // TfoNexon
};

constexpr const std::array<std::string_view, 5> PackageEntryKeys = {
    "\x6C\x6B\x67\x75\x69\x37\x38\x31\x6B\x6C\x37\x38\x39\x73\x64\x21\x40\x23\x25\x38\x39\x26\x5E\x73\x64"sv,  // Nexon
    "\x9B\x65\xC7\x9B\xC7\xDF\x8E\x7E\xD4\xC6\x59\x52\x5C\xF7\x22\xFF\xF4\xE8\xFF\xE7\xB5\xC2\x77"sv,  // Tiancity
    "\x86\x39\x53\xBD\x16\x11\x6D\x06\x2A\x84\xF3\x4E\xE0\x4A\xA3"sv,  // Beancity
    "\x6C\x6B\x67\x75\x69\x37\x38\x31\x6B\x6C\x37\x38\x39\x73\x64\x21\x40\x23\x25\x38\x39\x26\x5E\x73\x64"sv,  // NexonJP
    "\x6C\x6B\x67\x75\x69\x37\x38\x31\x6B\x6C\x37\x38\x39\x73\x64\x21\x40\x23\x25\x38\x39\x26\x5E\x73\x64"sv  // TfoNexon
};

constexpr const std::array<std::string_view, 5> PackageFileKeys = {
    "\x5E\x39\x67\x45\x72\x67\x32\x53\x78\x37\x62\x6E\x6B\x37\x40\x23\x73\x64\x66\x6A\x6E\x68\x40"sv,  // Nexon
    "\x8E\x5C\xB8\x92\x45\xD1\x90\xBA\x82\x0F\xD9\x7A\x99\x8E\xB3\x87\xF7"sv,  // Tiancity
    "\x1F\x9F\xF8\xF4\x18\xAC\x25\xA2\xBB\x37\x82\x6D\xA8\xAE\xA7\x28\xBA\xDD\xDD\xE4\x6B"sv,  // Beancity
    "\x5E\x39\x67\x45\x72\x67\x32\x53\x78\x37\x62\x6E\x6B\x37\x40\x23\x73\x64\x66\x6A\x6E\x68\x40"sv,  // NexonJP
    "\x5E\x39\x67\x45\x72\x67\x32\x53\x78\x37\x62\x6E\x6B\x37\x40\x23\x73\x64\x66\x6A\x6E\x68\x40"sv  // TfoNexon
};

constexpr const std::array<uint64_t, 5> PackageFileCounts = {
    7,   // Nexon
    10,  // Tiancity
    12,  // Beancity
    6,   // NexonJP
    0    // TfoNexon
};

using FileHashes_t = std::array<std::string_view, 12>;

constexpr const FileHashes_t NexonPackageFilesHashes = {
    "15f225c83b6a26dc856e0596d751e594927b6ff3644419cef86c94acd3aa576c",
    "ba32c9a36a489e0f88fde3b162508808be294833dfd728a0cff158f3afa53e2a",
    "1acfaf45a5365981d9032da9a105dcafce441e9cdb8c9adadd5a05c6f7dc6b62",
    "15b9d21fd053a2be5508c984dc2ffb838b1b868f0e355a2f050412a4a9172cb3",
    "94738e58dc4b59a5e1abda6469708bdcc645849a94c31f3d879918a4a2826de6",
    "9939d6b9f08802c7d727a90f6a435d62243a7df7b2c3ef3428bfc22164f9d252",
    "b9bf313f0f5e0c5d5648be520070682b9165c789ec482e89249863aec39b51d9",
};

constexpr const FileHashes_t TiancityPackageFilesHashes = {
    "56f02c73d2baa1ecc86ece2151eef3215eeae672e4a2a8ea5b3d624926240fcf",
    "7fc7d17194cd47d2fd67be36734d2eb44e31b266ab91b84557b8e0a7e36db62d",
    "b30d42695b33df7c8dfc7125036b4b892b28267e99cc2cc48ef6bf1e9eb0ff70",
    "361ae4cdbc48c00a1db3a64227fdb3b45ce2e5b5fa8e4cdcbdf1a11a7d4a793b",
    "7d1dc02267f11bd8c5f841056b26e68e744dba9cd2e4d2372e801da02dc246b3",
    "fd3ef53a2d59bad52ab952918f5e2076a06a418660fba8d14fbe755d4702e846",
    "a195d83e039e12e7a5be563c407271af01890d2041967133e6db26fe16dc3a22",
    "d958f56770274900c873eecef315bd24576e08a04d77d5f7a32e600ba99bb29b",
    "b5623b642d7c50f2540fc1bc362faf4191fede7bfb9a40c9985fd03f8b84596f",
    "ddeca19a3f7867a7da5661bbf9679ac7c7b084695b0e17715a25e4f49662be01",
};

constexpr const FileHashes_t BeancityPackageFilesHashes = {
    "f2223688ed9ca48b3434f60e8fcd9b3a73242346fe4f217745ee20b0ca1c2f55",
    "8712f8c405cb5ceb93d4d6139885cdeda46be636120d3acdeabe2f1e2613c314",
    "2ba82a5fb181933d718f4830243e6e3f9b73cef5f0c65519c33be11df8e94504",
    "ddf4fb486a921204df08515c1678d701cd1a89f216cc16ae2d7cb25ca6ed2097",
    "92eab2099928fcee2efe73b0fc08622c5bbf33d50285345dee69f3d4f5278b5b",
    "fd4926601cd0487e8dcc5c6270fb2d9d9c77de159a4163be210f97027754b740",
    "6e22c4772407d0e1b8f939b2caee2351582f025fca96e4c3927af67924f79f6d",
    "e89f519e3ad9734a1e7968907077d5ac91beb321ab021ba857a58eabe0a60e65",
    "ebd3c056d074735a6a14b4a32d631cc931d34a6d8e2fb74df26047f3bfa837f0",
    "b5e1d9439c81d15aeec3d270cc7aa7dccc2d0bb5a188f733bb8cdcd9796dd60e",
    "ee1aa62cbb4ec73157d0e3d8c6d886fc218f189c06bfaa7ac078ccbbdd5c4cab",
    "97df6d0877b1f5fa2c387f1f2154cf0995cd56b76c0ef064af4c6abb97926fd2",
};

constexpr const FileHashes_t NexonJpPackageFilesHashes = {
    "5b5f10858f6728d51eb7d96c1d690f1036f4acd4479ad909ea7d4160cd2869b5",
    "c126a6ce8e790bf7031dd9003c7658538aa8d37157b180e43c6b125c7686060e",
    "d3b25869e0255b845fe3283fcb21a6617ff5c9489729dbe176e9cf8b0c085dd6",
    "81a08777371a87fba363b82f606c57d273f9c398a6b6bc0ef71b3e1364fd37f5",
    "fec0b8efda72be3eeb3814689a53557cbbbac3e0eb7628e730ae0f6a793d1194",
    "e79a63ec06a0120c0559b2f309d82f807ef4afe281f5ded9c17d57c9967bda94",
};

constexpr const std::array<FileHashes_t, 5> PackageFilesHashes = {
    NexonPackageFilesHashes,     // Nexon
    TiancityPackageFilesHashes,  // Tiancity
    BeancityPackageFilesHashes,  // Beancity
    NexonJpPackageFilesHashes,   // NexonJP
    NexonJpPackageFilesHashes    // TfoNexon
};
//
// PKG data END
//

//
// Encrypted data START
//
constexpr const std::array<std::string_view, 4> EncryptedFileNames = {
    "attachments_dev_nexon.ecsv"sv,     // Nexon
    "attachments_dev_tiancity.ecsv"sv,  // Tiancity
    "attachments_beancity.ecsv"sv,      // Beancity
    "attachments_dev_nexonjp.ecsv"sv    // NexonJP
};

constexpr const std::array<std::string_view, 4> RealEncryptedFileNames = {
    "attachments_dev.ecsv"sv,  // Nexon
    "attachments_dev.ecsv"sv,  // Tiancity
    "attachments.ecsv"sv,      // Beancity
    "attachments_dev.ecsv"sv   // NexonJP
};

constexpr const std::array<std::string_view, 4> EncryptedFileHashes = {
    "6e36e63e2cb289c9d9cbe050c9a1f1c0816f3f52d688fe9d5a969e390f402476"sv,  // Nexon
    "acbfc0fb016a9b1a750fc37f8aa74bfd442585f88caf0953f7209e4ee44078ea"sv,  // Tiancity
    "9d2ae8d708410744ff813ac7fedf7060e625a36eff2f9f0129067353004bd0e7"sv,  // Beancity
    "522b9874a577f73241bc6343625061d566bd0caf4b0bf2e84956e1353117e176"sv  // NexonJP
};
//
// Encrypted data END
//

//
// LZMA texture START
//
constexpr const std::string_view TextureFilename = "v_m4a1_gold.vtf";
constexpr const std::string_view TextureFileHash =
    "cfe553bcbfdd3f2e948c4851deb5bbba7d3e041963999fe7d7980e08c97e079e"sv;
//
// LZMA texture END
//
}  // namespace cso2
