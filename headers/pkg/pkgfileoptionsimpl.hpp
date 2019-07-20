#pragma once

#include "pkgfileoptions.hpp"

namespace uc2
{
class PkgFileOptionsImpl : public PkgFileOptions
{
public:
    PkgFileOptionsImpl();
    virtual ~PkgFileOptionsImpl();

    virtual void SetTfoPkg(bool state);

    static ptr_t Create();

    virtual bool IsTfoPkg();

private:
    bool m_bIsTfoPkg;
};
}  // namespace uc2
