#pragma once

#include "pkgfileoptions.hpp"

namespace uc2
{
class PkgFileOptionsImpl : public PkgFileOptions
{
public:
    PkgFileOptionsImpl();
    virtual ~PkgFileOptionsImpl();

    virtual void SetTfoPkg(bool state) override;
    virtual bool IsTfoPkg() override;

    static ptr_t Create();

private:
    bool m_bIsTfoPkg;
};
}  // namespace uc2
