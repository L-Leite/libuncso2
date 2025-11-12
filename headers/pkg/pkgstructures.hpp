#pragma once

#include <cstdint>

namespace uc2
{
#pragma pack(push, 1)

struct PkgIndexHeader_t
{
    std::uint16_t iVersion;
    std::uint8_t iCipher;
    std::uint8_t iKey;
    std::uint32_t iFileSize;
};

static_assert(sizeof(PkgIndexHeader_t) == 8,
              "The pkg index header's size must be 8 bytes long");

struct PkgHeader_t
{
    // skip the hash since it's not encrypted
    // char szHash[32 + 1];
    char szDirectoryPath[260 + 1];
    std::uint32_t UnknownVal;  // it's always (?) zero, so we use it to validate
                               // the header
    std::uint32_t iEntries;
    std::uint8_t Pad[3];
};

static_assert(sizeof(PkgHeader_t) == 272,
              "The pkg header's size must be 272 bytes long");

struct PkgHeaderTfo_t
{
    // skip the hash since it's not encrypted
    // char szHash[32 + 1];
    std::uint32_t UnknownVal;  // it's always (?) zero, so we use it to validate
                               // the header
    std::uint32_t iEntries;
    std::uint32_t UnknownVal2;
    std::uint32_t Padding;
};

static_assert(sizeof(PkgHeaderTfo_t) == 16,
              "The TFO pkg header's size must be 16 bytes long");

struct PkgEntryHeader_t
{
    char szFilePath[260 + 1];
    std::uint32_t iOffset;
    std::uint32_t iEncryptedSize;
    std::uint32_t iDecryptedSize;
    std::uint8_t Unknown273;
    std::uint8_t bIsEncrypted;
    std::uint8_t Pad[13];
};

static_assert(sizeof(PkgEntryHeader_t) == 288,
              "The pkg entry header's size must be 288 bytes long");

struct PkgEntryHeaderTfo_t
{
    char szFilePath[260 + 1];
    std::uint64_t iOffset;
    std::uint64_t iEncryptedSize;
    std::uint64_t iDecryptedSize;
    std::uint8_t Unknown285;
    std::uint8_t bIsEncrypted;
    std::uint8_t Pad[1];
};

static_assert(sizeof(PkgEntryHeader_t) == 288,
              "The TFO pkg entry header's size must be 288 bytes long");

#pragma pack(pop)
}  // namespace uc2
