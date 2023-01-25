#include "Engine.h"

#include <Windows.h>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include <Bits.h>

uintptr_t Engine::GetClient() {
	return (uintptr_t)GetModuleHandle("client.dll");
}

uintptr_t Engine::GetEngine() {
	return (uintptr_t)GetModuleHandle("engine.dll");
}

Vector3* Engine::GetViewAngles() {
	uintptr_t engineModule = GetEngine();
	Vector3* viewAngles = (Vector3*)(*(uintptr_t*)(engineModule + Offsets::dwClientState) + Offsets::dwClientState_ViewAngles);

	return viewAngles;
}

void Engine::Shoot() {
	*(uintptr_t*)(GetClient() + Offsets::dwForceAttack) = 6;
}

void Engine::Jump(Ent* localPlayer) {
	(localPlayer->m_fFlags & (1 << 0)) ? 
		*(uintptr_t*)(GetClient() + Offsets::dwForceJump) = 6 : 
		*(uintptr_t*)(GetClient() + Offsets::dwForceJump) = 4;
}

void Engine::AimAt(Ent* localPlayer, Vector3 pos) {
	Vector3* viewAngles = GetViewAngles();

	Vector3 origin = localPlayer->vecOrigin;
	Vector3 viewOffset = localPlayer->vecViewOffset;
	Vector3 myPos = (origin + viewOffset);

	Vector2 angle = Math::CalcAngle(myPos, pos);

	if (angle.x >= -89 && angle.x <= 89 && angle.y >= -180 && angle.y <= 180)
	{
		viewAngles->x = angle.x;
		viewAngles->y = angle.y;
	}
}

bool Engine::CheckValidEnt(Ent* localPlayer, Ent* ent) {
	if (ent == nullptr)
		return false;
	if (ent == localPlayer)
		return false;
	if (ent->iHealth <= 0)
		return false;
	if (ent->isDormant)
		return false;

	return true;
}

int Engine::GetMaxPlayers() {
	return *(int*)(*(uintptr_t*)(GetEngine() + Offsets::dwClientState) + Offsets::dwClientState_MaxPlayer);
}

Ent* Engine::GetClosestPlayerByDist(Ent* localPlayer, EntList* entList) {
	float closestDitance = 1000000;
	int closesDistanceIndex = 1;

	for (size_t i = 0; i < GetMaxPlayers(); i++)
	{
		Ent* player = entList->ents[i].ent;

		if (!player || player == NULL || player == nullptr)
			continue;

		if (player == localPlayer)
			continue;

		if (player->iHealth< 1)
			continue;

		if (localPlayer->vecOrigin.Distance(player->vecOrigin) < closestDitance) {
			closestDitance = localPlayer->vecOrigin.Distance(player->vecOrigin);
			closesDistanceIndex = i;
		}
	}

	if (closesDistanceIndex == -1)
		return NULL;

	return entList->ents[closesDistanceIndex].ent;
}

Ent* Engine::GetClosestPlayerByFOV(Ent* localPlayer, EntList* entList, float FOV) {
	float closestAngle = 1000000;
	int closesAngleIndex = -1;

	for (size_t i = 0; i < GetMaxPlayers(); i++)
	{
		Ent* player = entList->ents[i].ent;

		if (!player || player == NULL || player == nullptr)
			continue;

		if (player == localPlayer)
			continue;

		if (player->iHealth < 1)
			continue;

		Vector3 playerPos = (player->vecOrigin + player->vecViewOffset);
		Vector3 localPos = (localPlayer->vecOrigin + localPlayer->vecViewOffset);

		Vector3 diffs = (Vector3(Math::CalcAngle(localPos, playerPos).x, Math::CalcAngle(localPos, playerPos).y, 0) - *Engine::GetViewAngles()).Abs();

		if (diffs.x > 180)
			diffs.x -= 360;

		if (diffs.x < -180)
			diffs.x += 360;

		if (diffs.Length3D() > (FOV + (FOV / 2.7)))
			continue;

		if (diffs.Length3D() < closestAngle) {
			closestAngle = diffs.Length3D();
			closesAngleIndex = i;
		}
	}

	if (closesAngleIndex == -1)
		return NULL;

	return entList->ents[closesAngleIndex].ent;
}

Vector3 Engine::GetBonePos(Ent* ent, int bone) {
	uintptr_t bonePtr = ent->boneMatrix;
	Vector3 bonePos;
	bonePos.x = *(float*)(bonePtr + 0x30 * bone + 0x0C);
	bonePos.y = *(float*)(bonePtr + 0x30 * bone + 0x1C);
	bonePos.z = *(float*)(bonePtr + 0x30 * bone + 0x2C);
	return bonePos;
}

ViewMatrix Engine::GetViewMatrix() {
	ViewMatrix tempMatrix;
	memcpy(&tempMatrix.matrix, (PBYTE*)(Engine::GetClient() + Offsets::dwViewMatrix), sizeof(tempMatrix.matrix));

	return tempMatrix;
}