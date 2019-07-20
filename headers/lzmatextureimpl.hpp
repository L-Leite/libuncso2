#pragma once

#include "lzmatexture.hpp"

#include <gsl/gsl>

namespace uc2
{
constexpr const uint8_t CSO2_LZMA_VTF_HWORD_SIGNATURE = 'C';      // C
constexpr const uint16_t CSO2_LZMA_VTF_LWORD_SIGNATURE = 0x324F;  // 02

#pragma pack(push, 1)

struct LzmaVtfHeader_t
{
    struct
    {
        uint8_t iHighByte;
        uint16_t iLowWord;
    } Signature;
    uint8_t iProbs;
    uint32_t iOriginalSize;
    uint32_t iChunkSizes[];  // TODO: can this flexible array be changed to
                             // something else?
};

#pragma pack(pop)

class LzmaTextureImpl : public LzmaTexture
{
public:
    LzmaTextureImpl(std::vector<uint8_t>& texData);
    LzmaTextureImpl(gsl::span<uint8_t> texDataView);
    virtual ~LzmaTextureImpl();

    virtual uint64_t GetOriginalSize();

    virtual bool Decompress(uint8_t* outBuffer, uint64_t outBufferSize);

    static ptr_t CreateSpan(gsl::span<uint8_t> texDataView);

private:
    bool IsHeaderValid() const;

private:
    gsl::span<uint8_t> m_TexDataView;
};
}  // namespace uc2
