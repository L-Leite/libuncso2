#include "lzmatextureimpl.hpp"

#include <assert.h>
#include <stdexcept>

#include "lzmaDecoder.h"

namespace uc2
{
LzmaTexture::ptr_t LzmaTexture::Create(std::vector<uint8_t>& texData)
{
    return std::make_unique<LzmaTextureImpl>(texData);
}

LzmaTexture::ptr_t LzmaTextureImpl::CreateSpan(gsl::span<uint8_t> texDataView)
{
    return std::make_unique<LzmaTextureImpl>(texDataView);
}

LzmaTextureImpl::LzmaTextureImpl(std::vector<uint8_t>& texData)
    : m_TexDataView(texData)
{
    if (this->IsHeaderValid() == false)
    {
        throw std::invalid_argument("libuncso2: The file's header is invalid");
    }
}

LzmaTextureImpl::LzmaTextureImpl(gsl::span<uint8_t> texDataView)
    : m_TexDataView(texDataView)
{
    if (this->IsHeaderValid() == false)
    {
        throw std::invalid_argument("libuncso2: The file's header is invalid");
    }
}

LzmaTextureImpl::~LzmaTextureImpl() {}

uint64_t LzmaTextureImpl::GetOriginalSize()
{
    auto pHeader =
        reinterpret_cast<LzmaVtfHeader_t*>(this->m_TexDataView.data());

    return pHeader->iOriginalSize;
}

bool LzmaTextureImpl::Decompress(uint8_t* outBuffer, uint64_t outBufferSize)
{
    auto pHeader =
        reinterpret_cast<LzmaVtfHeader_t*>(this->m_TexDataView.data());

    if (pHeader->iOriginalSize != outBufferSize)
    {
        return false;
    }

    uint8_t* pBuffer = reinterpret_cast<uint8_t*>(this->m_TexDataView.data());
    uint32_t iOutOffset = 0;

    CLZMA lzma;

    for (uint8_t i = 0; i < pHeader->iProbs; i++)
    {
        uint32_t iChunkSize = pHeader->iChunkSizes[i * 2];
        uint8_t* pChunk = pBuffer + (iChunkSize >> 1);
        bool bIsCompressed = iChunkSize & 1;

        unsigned int outSize;

        if (bIsCompressed)
        {
            outSize = lzma.Uncompress(pChunk, outBuffer + iOutOffset);
        }
        else
        {
            outSize = pHeader->iChunkSizes[i * 2 + 1];
            std::copy(pChunk, pChunk + outSize, outBuffer + iOutOffset);
        }

        iOutOffset += outSize;
    }

    if (pHeader->iOriginalSize != iOutOffset)
    {
        return false;
    }

    return true;
}

bool LzmaTextureImpl::IsHeaderValid() const
{
    const uint64_t iFileDataSize = this->m_TexDataView.size_bytes();

    if (iFileDataSize < sizeof(LzmaVtfHeader_t))
    {
        return false;
    }

    auto pHeader =
        reinterpret_cast<LzmaVtfHeader_t*>(this->m_TexDataView.data());

    if (iFileDataSize < sizeof(LzmaVtfHeader_t))
    {
        return false;
    }

    return pHeader->Signature.iHighByte == CSO2_LZMA_VTF_HWORD_SIGNATURE &&
           pHeader->Signature.iLowWord == CSO2_LZMA_VTF_LWORD_SIGNATURE;
}
}  // namespace uc2
