#pragma once

// The following will ensure correct symbol export/import in different environments
#ifdef MYLIBRARY_EXPORTS
#define MYLIBRARY_API __declspec(dllexport)
#else
#define MYLIBRARY_API __declspec(dllimport)
#endif

extern "C" {
    // Example function declarations
    MYLIBRARY_API int Add(int a, int b);
    MYLIBRARY_API int Multiply(int a, int b);
}
