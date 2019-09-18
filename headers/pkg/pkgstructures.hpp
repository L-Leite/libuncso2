#pragma once

#include <cstdint>

namespace uc2
{
#pragma pack(push, 1)

struct PkgIndexHeader_t
{
    uint16_t iVersion;
    uint8_t iCipher;
    uint8_t iKey;
    uint32_t iFileSize;
};

static_assert(sizeof(PkgIndexHeader_t) == 8,
              "The pkg index header's size must be 8 bytes long");

struct PkgHeader_t
{
    // skip the hash since it's not encrypted
    // char szHash[32 + 1];
    char szDirectoryPath[260 + 1];
    uint32_t UnknownVal;  // it's always (?) zero, so we use it to validate the
                          // header
    uint32_t iEntries;
    uint8_t Pad[3];
};

static_assert(sizeof(PkgHeader_t) == 272,
              "The pkg header's size must be 272 bytes long");

struct PkgHeaderTfo_t
{
    // skip the hash since it's not encrypted
    // char szHash[32 + 1];
    uint32_t UnknownVal;  // it's always (?) zero, so we use it to validate the
                          // header
    uint32_t iEntries;
    uint32_t UnknownVal2;
    uint32_t Padding;
};

static_assert(sizeof(PkgHeaderTfo_t) == 16,
              "The TFO pkg header's size must be 16 bytes long");

struct PkgEntryHeader_t
{
    char szFilePath[260 + 1];
    uint32_t iOffset;
    uint32_t iEncryptedSize;
    uint32_t iDecryptedSize;
    uint8_t Unknown273;
    uint8_t bIsEncrypted;
    uint8_t Pad[13];
};

static_assert(sizeof(PkgEntryHeader_t) == 288,
              "The pkg entry header's size must be 288 bytes long");

#pragma pack(pop)
}  // namespace uc2
