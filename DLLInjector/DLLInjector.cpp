/* 
1. Find target process by name or PID
2. Open target process with necessary permissions
3. Allocate memory in target process for the path to DLL.
4. Write the path of DLL into the allocated memory
5. Use CreateRemoteThread to start a thread in the target process that loads the DLL using LoadLibrary
*/

#include <iostream>
#include <Windows.h>

int main()
{
    // path to our dll
    LPCSTR DllPath = "C:\\Users\\ArchMage\\source\\DLL Dev\\build\\InjectLibrary";

    DWORD process_id;
    std::cout << "Enter Process ID (PID): " << std::endl;
    std::cin >> process_id;

    // Open a handle to target process
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);

    // Allocate memory for the dllpath in the target process
    // length of the path string + null terminator
    LPVOID pDllPath = VirtualAllocEx(hProcess, 0, strlen(DllPath) + 1, MEM_COMMIT, PAGE_READWRITE);

    // Write the path to the address of the memory
    // we just allocated in the target process
    WriteProcessMemory(hProcess, pDllPath, (LPVOID)DllPath, strlen(DllPath) + 1, 0);

    // Create a Remote Thread in the target process which
    // calls LoadLibraryA as our dllpath as an argument -> program loads our dll
    HANDLE hLoadThread = CreateRemoteThread(
        hProcess, 0, 0, 
        (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"),
        "LoadLibraryA"), pDllPath, 0, 0
    );

    // Wait for the execution of our loader thread to finish
    WaitForSingleObject(hLoadThread, INFINITE);

    std::cout << "Dll path allocated at: " << std::hex << pDllPath << std::endl;
    std::cin.get();

    system("pause");

    // Free the memory allocated for our dll path
    VirtualFreeEx(hProcess, pDllPath, strlen(DllPath) + 1, MEM_RELEASE);

    system("pause");

    return 0;
}