#pragma once

#include "Ent.h"

namespace Engine
{
	uintptr_t GetClient();
	uintptr_t GetEngine();

	Vector3* GetViewAngles();
	Vector3 GetBonePos(Ent* ent, int bone);

	ViewMatrix GetViewMatrix();

	bool CheckValidEnt(Ent* localPlayer, Ent* ent);

	void Shoot();
	void Jump(Ent* localPlayer);

	void AimAt(Ent* localPlayer, Vector3 pos);

	Ent* GetClosestPlayerByDist(Ent* localPlayer, EntList* entList);
	Ent* GetClosestPlayerByFOV(Ent* localPlayer, EntList* entList, float FOV);

	int GetMaxPlayers();
};

