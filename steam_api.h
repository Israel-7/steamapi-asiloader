#pragma once

#ifndef STEAM_API_H
#define STEAM_API_H

#include <windows.h>

class Loader {
public:
    static VOID loadASIs();
    static BOOL init();
};

#endif
