// InjectLibrary.h
#pragma once
#ifdef INJECTEDLIBRARY_EXPORTS
#define INJECTEDLIBRARY_API __declspec(dllexport)
#else
#define INJECTEDLIBRARY_API __declspec(dllimport)
#endif

extern "C" {
    INJECTEDLIBRARY_API void InjectedFunction();
}