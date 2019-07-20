#include <catch2/catch.hpp>

#include <iostream>
#include <string_view>

#include <uc2/uc2.h>
#include <uc2/uc2.hpp>

#include "cso2/nexon/settings.hpp"
#include "utils.hpp"

using namespace std::literals::string_view_literals;

TEST_CASE("Pkg file can be decrypted and parsed", "[pkgfile]")
{
    SECTION("Can parse entries")
    {
        for (size_t i = 0; i < cso2::NUM_PROVIDERS; i++)
        {
            auto [bWasRead, vFileBuffer] =
                ReadFileToBuffer(cso2::PkgFilenames[i]);

            REQUIRE(bWasRead == true);
            REQUIRE(vFileBuffer.empty() == false);

            try
            {
                auto pPkgFile = uc2::PkgFile::Create(
                    cso2::PkgFilenames[i], vFileBuffer,
                    cso2::PackageEntryKeys[i], cso2::PackageFileKeys[i]);
                pPkgFile->Parse();

                REQUIRE(pPkgFile->GetEntries().size() ==
                        cso2::PackageFileCounts[i]);

                size_t iCurIndex = 0;
                for (auto&& entry : pPkgFile->GetEntries())
                {
                    auto [fileData, fileDataLen] = entry->DecryptFile();
                    REQUIRE(GetDataHash(fileData, fileDataLen) ==
                            cso2::PackageFilesHashes[i][iCurIndex]);

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
}

TEST_CASE("Pkg file can be decrypted and parsed using C bindings", "[pkgfile]")
{
    SECTION("Can parse entries")
    {
        for (size_t i = 0; i < cso2::NUM_PROVIDERS; i++)
        {
            auto [bWasRead, vFileBuffer] =
                ReadFileToBuffer(cso2::PkgFilenames[i]);

            REQUIRE(bWasRead == true);
            REQUIRE(vFileBuffer.empty() == false);

            PkgFile_t pPkg = uncso2_PkgFile_Create(
                cso2::PkgFilenames[i].data(), vFileBuffer.data(),
                vFileBuffer.size(), cso2::PackageEntryKeys[i].data(),
                cso2::PackageFileKeys[i].data());
            REQUIRE(pPkg != NULL);

            bool bWasParsed = uncso2_PkgFile_Parse(pPkg);
            REQUIRE(bWasParsed == true);

            uint64_t iEntriesNum = uncso2_PkgFile_GetEntriesNum(pPkg);
            PkgEntry_t* pEntries = uncso2_PkgFile_GetEntries(pPkg);

            REQUIRE(iEntriesNum == cso2::PackageFileCounts[i]);

            for (size_t y = 0; y < iEntriesNum; y++)
            {
                void* pOutBuffer;
                uint64_t iOutBufferSize;
                bool bValidEntry = uncso2_PkgEntry_Decrypt(
                    pEntries[y], &pOutBuffer, &iOutBufferSize);

                REQUIRE(bValidEntry == true);
                REQUIRE(GetDataHash(reinterpret_cast<uint8_t*>(pOutBuffer),
                                    iOutBufferSize) ==
                        cso2::PackageFilesHashes[i][y]);
            }

            uncso2_PkgFile_Free(pPkg);
        }
    }
}
