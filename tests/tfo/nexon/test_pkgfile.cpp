#include <catch2/catch.hpp>

#include <iostream>
#include <string_view>

#include <uc2/uc2.h>
#include <uc2/uc2.hpp>

#include "tfo/nexon/settings.hpp"
#include "utils.hpp"

using namespace std::literals::string_view_literals;

TEST_CASE("TFO Pkg file can be decrypted and parsed", "[pkgfile]")
{
    SECTION("Can parse entries")
    {
        auto [bWasRead, vFileBuffer] = ReadFileToBuffer(tfo::PkgFilename);

        REQUIRE(bWasRead == true);
        REQUIRE(vFileBuffer.empty() == false);

        try
        {
            auto pPkgOptions = uc2::PkgFileOptions::Create();
            pPkgOptions->SetTfoPkg(true);

            auto pPkgFile = uc2::PkgFile::Create(
                tfo::PkgFilename, vFileBuffer, tfo::PackageEntryKey,
                tfo::PackageFileKey, pPkgOptions.get());

            pPkgFile->DecryptHeader();
            pPkgFile->Parse();

            REQUIRE(pPkgFile->GetEntries().size() == tfo::PackageFileCount);

            std::size_t iCurIndex = 0;
            for (auto&& entry : pPkgFile->GetEntries())
            {
                fs::path entryPath = entry->GetFilePath();
                auto [fileData, fileDataLen] = entry->DecryptFile();
                REQUIRE(GetDataHash(fileData, fileDataLen) ==
                        tfo::PackageFileHashes[iCurIndex]);

                iCurIndex++;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw e;
        }
    }
}

TEST_CASE("TFO Pkg file partially decrypting an entry", "[pkgfile]")
{
    SECTION("Can decrypt 16 bytes of an entry")
    {
        auto [bWasRead, vFileBuffer] = ReadFileToBuffer(tfo::PkgFilename);

        REQUIRE(bWasRead == true);
        REQUIRE(vFileBuffer.empty() == false);

        try
        {
            auto pPkgOptions = uc2::PkgFileOptions::Create();
            pPkgOptions->SetTfoPkg(true);

            auto pPkgFile = uc2::PkgFile::Create(
                tfo::PkgFilename, vFileBuffer, tfo::PackageEntryKey,
                tfo::PackageFileKey, pPkgOptions.get());

            pPkgFile->DecryptHeader();
            pPkgFile->Parse();

            REQUIRE(pPkgFile->GetEntries().size() == tfo::PackageFileCount);

            constexpr const std::uint64_t iTargetFileLen = 16;

            auto&& entry = pPkgFile->GetEntries().at(0);
            auto [fileData, fileDataLen] = entry->DecryptFile(iTargetFileLen);

            REQUIRE(fileDataLen == iTargetFileLen);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw e;
        }
    }
    SECTION("Can decrypt 23 bytes of an entry")
    {
        auto [bWasRead, vFileBuffer] = ReadFileToBuffer(tfo::PkgFilename);

        REQUIRE(bWasRead == true);
        REQUIRE(vFileBuffer.empty() == false);

        try
        {
            auto pPkgOptions = uc2::PkgFileOptions::Create();
            pPkgOptions->SetTfoPkg(true);

            auto pPkgFile = uc2::PkgFile::Create(
                tfo::PkgFilename, vFileBuffer, tfo::PackageEntryKey,
                tfo::PackageFileKey, pPkgOptions.get());

            pPkgFile->DecryptHeader();
            pPkgFile->Parse();

            REQUIRE(pPkgFile->GetEntries().size() == tfo::PackageFileCount);

            constexpr const std::uint64_t iTargetFileLen = 23;
            constexpr const std::uint64_t iExpectedFileLen = 32;

            auto&& entry = pPkgFile->GetEntries().at(0);
            auto [fileData, fileDataLen] = entry->DecryptFile(iTargetFileLen);

            REQUIRE(fileDataLen == iExpectedFileLen);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw e;
        }
    }
}

TEST_CASE("TFO Pkg file can be decrypted and parsed using C bindings",
          "[pkgfile]")
{
    SECTION("Can parse entries")
    {
        auto [bWasRead, vFileBuffer] = ReadFileToBuffer(tfo::PkgFilename);

        REQUIRE(bWasRead == true);
        REQUIRE(vFileBuffer.empty() == false);

        PkgFileOptions_t pOptions = uncso2_PkgFileOptions_Create();
        REQUIRE(pOptions != NULL);

        uncso2_PkgFileOptions_SetTfoPkg(pOptions, true);

        PkgFile_t pPkg = uncso2_PkgFile_Create(
            tfo::PkgFilename.data(), vFileBuffer.data(), vFileBuffer.size(),
            tfo::PackageEntryKey.data(), tfo::PackageFileKey.data(), pOptions);
        REQUIRE(pPkg != NULL);

        uncso2_PkgFileOptions_Free(pOptions);

        bool bHeaderDecrypted = uncso2_PkgFile_DecryptHeader(pPkg);
        REQUIRE(bHeaderDecrypted == true);

        bool bParsed = uncso2_PkgFile_Parse(pPkg);
        REQUIRE(bParsed == true);

        std::uint64_t iEntriesNum = uncso2_PkgFile_GetEntriesNum(pPkg);
        PkgEntry_t* pEntries = uncso2_PkgFile_GetEntries(pPkg);

        REQUIRE(iEntriesNum == tfo::PackageFileCount);

        for (std::size_t y = 0; y < iEntriesNum; y++)
        {
            void* pOutBuffer;
            std::uint64_t iOutBufferSize;
            bool bValidEntry = uncso2_PkgEntry_Decrypt(pEntries[y], &pOutBuffer,
                                                       &iOutBufferSize);

            REQUIRE(bValidEntry == true);
            REQUIRE(GetDataHash(reinterpret_cast<std::uint8_t*>(pOutBuffer),
                                iOutBufferSize) == tfo::PackageFileHashes[y]);
        }

        uncso2_PkgFile_Free(pPkg);
    }
}
