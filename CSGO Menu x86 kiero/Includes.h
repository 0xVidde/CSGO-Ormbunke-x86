#pragma once
#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <thread>
#include <chrono>
#include "Includes/kiero/kiero.h"
#include "Includes/kiero/minhook/include/MinHook.h"
#include "Includes/imgui/imgui.h"
#include "Includes/imgui/imgui_impl_win32.h"
#include "Includes/imgui/imgui_impl_dx9.h"

#define WINDOW_NAME "Ormbunke x86"
typedef long(__stdcall* EndScene)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);