
#include <windows.h>
#include <iostream>
#include <cwchar>
#include <TlHelp32.h>
#pragma warning( disable : 6387 )
BOOL EnableDebugPrivilege(BOOL bEnable)
{
    HANDLE hToken = NULL;

    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
        return FALSE;

    LUID luid;
    if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luid))
        return FALSE;

    TOKEN_PRIVILEGES tokenPriv;
    tokenPriv.PrivilegeCount = 1;
    tokenPriv.Privileges[0].Luid = luid;
    tokenPriv.Privileges[0].Attributes = bEnable ? SE_PRIVILEGE_ENABLED : 0;

    if (!AdjustTokenPrivileges(hToken, FALSE, &tokenPriv, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
        return FALSE;

    return TRUE;
}
DWORD GetProcId(const wchar_t* procName)
{
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        //PROCESSENTRY32 procEntry;
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!_wcsicmp(procEntry.szExeFile, procName))
                {
                    procId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return procId;
}
int main()
{
    const char* dllPath = "C:\\Users\\Konstrictor\\Documents\\..ram\\DLL\\ram_dll.dll";
    const wchar_t* procName = TEXT("Cemu.exe");
    DWORD procId = 0;
    std::cout << "Looking for Cemu...\n";
    while (!procId)
    {
        procId = GetProcId(procName);
        Sleep(30);
    }
    std::cout << "Found Cemu; Opening process...\n";
    std::cout << EnableDebugPrivilege(TRUE);
    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

    if (hProc && hProc != INVALID_HANDLE_VALUE)
    {
        std::cout << "Allocating Memory...\n";
        void* loc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
        std::cout << "Writing Memory...\n";
        BOOL wrote = WriteProcessMemory(hProc, loc, dllPath, strlen(dllPath) + 1, 0);
        std::cout << "Wrote? " << (wrote ? "Yes!" : "No :(") << "\n";
        HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, loc, 0, 0);

        if (hThread)
        {
            CloseHandle(hThread);
        }
    }
    if (hProc)
    {
        CloseHandle(hProc);
    }
    return 0;
}
