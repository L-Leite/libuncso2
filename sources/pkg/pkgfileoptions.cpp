#include "pkg/pkgfileoptionsimpl.hpp"

namespace uc2
{
PkgFileOptions::ptr_t PkgFileOptions::Create()
{
    return std::make_unique<PkgFileOptionsImpl>();
}

PkgFileOptionsImpl::PkgFileOptionsImpl() : m_bIsTfoPkg(false) {}

PkgFileOptionsImpl::~PkgFileOptionsImpl() {}

void PkgFileOptionsImpl::SetTfoPkg(bool state)
{
    this->m_bIsTfoPkg = state;
}

bool PkgFileOptionsImpl::IsTfoPkg()
{
    return m_bIsTfoPkg;
}
}  // namespace uc2