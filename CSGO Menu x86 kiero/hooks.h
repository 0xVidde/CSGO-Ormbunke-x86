#pragma once
#include "Includes.h"

static EndScene oEndScene = NULL;
static WNDPROC oWndProc;
static HWND window = NULL;
 
namespace hooks {
	void Init();
}