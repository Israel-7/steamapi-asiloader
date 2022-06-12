#include "steam_api.h"

VOID Loader::loadASIs()
{
    WIN32_FIND_DATA fdata;
    HANDLE hFind = FindFirstFile(L"*.asi", &fdata);
    
    if (hFind)
    {
        do {
            LoadLibrary(fdata.cFileName);
        } while (FindNextFile(hFind, &fdata));

        FindClose(hFind);
    }

    static BOOL loaded = FALSE;

    if (!loaded)
    {
        loaded = TRUE;
        
        if (SetCurrentDirectory(L"plugins")) {
            loadASIs();
        }
    }
}

LPVOID _SteamUserStats,
_SteamAPI_UnregisterCallback,
_SteamAPI_RegisterCallback,
_SteamAPI_RunCallbacks,
_SteamAPI_Init,
_SteamAPI_Shutdown,
_SteamUser;

extern "C" {
    __declspec(dllexport, naked) int SteamUserStats()
    { _asm jmp _SteamUserStats }

    __declspec(dllexport, naked) void SteamAPI_UnregisterCallback()
    { _asm jmp _SteamAPI_UnregisterCallback }

    __declspec(dllexport, naked) void SteamAPI_RegisterCallback(int, int)
    { _asm jmp _SteamAPI_RegisterCallback }

    __declspec(dllexport, naked) int SteamAPI_RunCallbacks()
    { _asm jmp _SteamAPI_RunCallbacks }

    __declspec(dllexport, naked) __int8 SteamAPI_Init(void*)
    { _asm jmp _SteamAPI_Init }

    __declspec(dllexport, naked) void SteamAPI_Shutdown()
    { _asm jmp _SteamAPI_Shutdown }

    __declspec(dllexport, naked) int SteamUser()
    { _asm jmp _SteamUser }
}

BOOL Loader::init()
{
    HMODULE steam_api_Hooked = LoadLibrary(L"steam_api_Hooked.dll");

    if (steam_api_Hooked)
    {
        _SteamUserStats = GetProcAddress(steam_api_Hooked, "SteamUserStats");
        _SteamAPI_UnregisterCallback = GetProcAddress(steam_api_Hooked, "SteamAPI_UnregisterCallback");
        _SteamAPI_RegisterCallback = GetProcAddress(steam_api_Hooked, "SteamAPI_RegisterCallback");
        _SteamAPI_RunCallbacks = GetProcAddress(steam_api_Hooked, "SteamAPI_RunCallbacks");
        _SteamAPI_Init = GetProcAddress(steam_api_Hooked, "SteamAPI_Init");
        _SteamAPI_Shutdown = GetProcAddress(steam_api_Hooked, "SteamAPI_Shutdown");
        _SteamUser = GetProcAddress(steam_api_Hooked, "SteamUser");
        
        return TRUE;
    }

    return FALSE;
}
