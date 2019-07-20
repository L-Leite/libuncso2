#include <catch2/catch.hpp>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>

#include <uc2/uc2.h>
#include <uc2/uc2.hpp>

#include "cso2/nexon/settings.hpp"
#include "utils.hpp"

using namespace std::literals::string_view_literals;

TEST_CASE("Can decompress LZMA'd VTFs", "[lzmavtf]")
{
    SECTION("Decompressing texture file")
    {
        auto [bWasRead, vIndexBuffer] = ReadFileToBuffer(cso2::TextureFilename);

        REQUIRE(bWasRead == true);
        REQUIRE(vIndexBuffer.empty() == false);

        try
        {
            auto pTex = uc2::LzmaTexture::Create(vIndexBuffer);

            uint64_t iOrigSize = pTex->GetOriginalSize();
            REQUIRE(iOrigSize != 0);

            std::vector<uint8_t> buff(iOrigSize);
            bool bDecompressed = pTex->Decompress(buff.data(), buff.size());

            REQUIRE(bDecompressed == true);
            REQUIRE(GetDataHash(buff.data(), buff.size()) ==
                    cso2::TextureFileHash);
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            throw e;
        }
    }
}

TEST_CASE("Can decompress LZMA'd VTFs with C bindings", "[lzmavtf]")
{
    SECTION("Decompressing texture file")
    {
        auto [bWasRead, vIndexBuffer] = ReadFileToBuffer(cso2::TextureFilename);

        REQUIRE(bWasRead == true);
        REQUIRE(vIndexBuffer.empty() == false);

        LzmaTexture_t pTexture =
            uncso2_LzmaTexture_Create(vIndexBuffer.data(), vIndexBuffer.size());
        REQUIRE(pTexture != NULL);

        uint64_t iOrigSize = uncso2_LzmaTexture_GetOriginalSize(pTexture);
        REQUIRE(iOrigSize != 0);

        void* pOutBuf = malloc(iOrigSize);
        REQUIRE(pOutBuf != NULL);

        bool bWasDecompressed =
            uncso2_LzmaTexture_Decompress(pTexture, pOutBuf, iOrigSize);

        REQUIRE(bWasDecompressed == true);
        REQUIRE(GetDataHash(reinterpret_cast<uint8_t*>(pOutBuf), iOrigSize) ==
                cso2::TextureFileHash);

        free(pOutBuf);
        uncso2_LzmaTexture_Free(pTexture);
    }
}
