#include "Utils.h"

#include <sstream>
#include <string>
#include <iostream>

#include <thread>       
#include <chrono>       

HWND window;

BOOL Utils::IsInFullscreen() {
    // Get the handle to the foreground window
    HWND foregroundWindow = GetForegroundWindow();
    if (foregroundWindow == NULL) {
        return FALSE;
    }

    // Get the dimensions of the screen
    RECT screenRect;
    if (!GetClientRect(GetDesktopWindow(), &screenRect)) {
        return FALSE;
    }

    // Get the dimensions of the foreground window
    RECT windowRect;
    if (!GetWindowRect(foregroundWindow, &windowRect)) {
        return FALSE;
    }

    // Compare the dimensions of the window to the dimensions of the screen
    if (windowRect.right == screenRect.right &&
        windowRect.bottom == screenRect.bottom &&
        windowRect.left == screenRect.left &&
        windowRect.top == screenRect.top) {
        return TRUE;
    }

    return FALSE;
}

BOOL CALLBACK enumWind(HWND handle, LPARAM lp) {
    DWORD procId;
    GetWindowThreadProcessId(handle, &procId);
    if (GetCurrentProcessId() != procId)
        return TRUE;

    window = handle;
    return FALSE;
}

Vector2 Utils::GetWindowRes() {
    window = NULL;
    EnumWindows(enumWind, NULL);

    RECT size;
    GetWindowRect(window, &size);

    Vector2 res;
    if (!IsInFullscreen())
        res = Vector2(size.right - size.left - 5, size.bottom - size.top - 29);
    else
        res = Vector2(size.right - size.left, size.bottom - size.top);

    return res;
}
