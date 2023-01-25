#pragma once

#include "Ent.h"

namespace Hack {
	void Init();
	void Update();

	void Aimbot();
	void BHop();
	void TriggerBot();
	void NoFlash();

	Ent* GetLocalPlayer();
	EntList* GetEntityList();
};