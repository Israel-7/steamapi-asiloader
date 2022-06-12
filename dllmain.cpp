#include "steam_api.h"

BOOL WINAPI DllMain(
    _In_ HINSTANCE hinstDLL,
    _In_ DWORD fdwReason,
    _In_ LPVOID lpvReserved
) {
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        if (Loader::init()) {
            Loader::loadASIs();
        }
    }

    return TRUE;
}
