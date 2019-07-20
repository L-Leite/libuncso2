/**
 * @file uc2defs.hpp
 * @author Luís Leite (luis@leite.xyz)
 * @brief Base definitions for libuncso2
 * @version 1.0
 */

#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef _WINDOWS
#if defined(UNCSO2_EXPORT)
#define UNCSO2_API __declspec(dllexport)
#elif defined(UNCSO2_STATIC)
#define UNCSO2_API
#else
#define UNCSO2_API __declspec(dllimport)
#endif  // UNCSO2_EXPORT
#else
#define UNCSO2_API
#endif  // _WINDOWS

#ifdef _MSC_VER
#ifdef _WIN64
#define UNCSO2_CALLMETHOD
#else
#define UNCSO2_CALLMETHOD __cdecl
#endif  // _WIN64
#elif defined(__GNUC__)
#ifdef __x86_64__
#define UNCSO2_CALLMETHOD
#else
#define UNCSO2_CALLMETHOD __attribute__((__cdecl__))
#endif  // __x86_64__
#else
#endif  // _MSC_VER

typedef void* EncryptedFile_t;
typedef void* LzmaTexture_t;
typedef void* PkgEntry_t;
typedef void* PkgFile_t;
typedef void* PkgFileOptions_t;
typedef void* PkgIndex_t;
