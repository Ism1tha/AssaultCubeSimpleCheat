#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <Windows.h>
#include <iostream>

void showInjectionStatus();

DWORD moduleBase;
DWORD localPlayer;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH) 
    {
        DWORD moduleBase = (DWORD)GetModuleHandle(L"ac_client.exe");
        DWORD localPlayer = *(DWORD*)(moduleBase + 0x18AC00);
        DWORD playerHealth = *(int*)(localPlayer + 0xEC);
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        std::cout << "moduleBase: " << moduleBase << "\n";
        std::cout << "localPlayer: " << localPlayer << "\n";
        std::cout << "playerHealth: " << playerHealth << "\n";

        *(DWORD*)(localPlayer + 0xEC) = 1337;
    }
    return true;
}
