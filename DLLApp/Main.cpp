#include <iostream>
#include <windows.h>  // For LoadLibrary and GetProcAddress

typedef int(*AddFunc)(int, int);       // Define function pointer types
typedef int(*MultiplyFunc)(int, int);

int main() {
    // Load the DLL at runtime
    HINSTANCE hDLL = LoadLibrary(TEXT("MyLibrary.dll"));
    if (hDLL == NULL) {
        std::cout << "Could not load the DLL!" << std::endl;
        system("pause");
        return 1;
    }

    // Get the function addresses
    AddFunc Add = (AddFunc)GetProcAddress(hDLL, "Add");
    MultiplyFunc Multiply = (MultiplyFunc)GetProcAddress(hDLL, "Multiply");

    if (!Add || !Multiply) {
        std::cout << "Could not locate the functions!" << std::endl;
        FreeLibrary(hDLL);
        system("pause");
        return 1;
    }

    // Call the functions using the function pointers
    int result1 = Add(5, 10);
    int result2 = Multiply(5, 10);

    std::cout << "Add(5, 10) = " << result1 << std::endl;
    std::cout << "Multiply(5, 10) = " << result2 << std::endl;

    // Free the DLL
    FreeLibrary(hDLL);
    system("pause");
    return 0;
}
