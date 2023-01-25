#include "Hack.h"

#include <Windows.h>
#include <iostream>

#include "gui.h"
#include "Engine.h"

#include <thread>
#include <chrono>

uintptr_t engine;
uintptr_t client;
Ent* localEnt;
EntList* entList;
float viewMatrix[16];

struct GlowStruct {
	float red = 1.f;
	float green = 0.f;
	float blue = 0.f;
	float alpha = 1.f;
	uint8_t padding[8];
	float unknown = 1.f;
	uint8_t padding2[4];
	BYTE renderOccluded = true;
	BYTE renderUnoccluded = false;
	BYTE fullBloom = false;
}GlowStructVar;

void Hack::Aimbot() {
	if (!gui::Config::aimbotOn)
		return;

	if (!GetAsyncKeyState(0x43))
		return;

	for (int i = 1; i < 32; i++) {
		Ent* p = Engine::GetClosestPlayerByFOV(localEnt, entList, gui::Config::fov_value);

		if (!Engine::CheckValidEnt(localEnt, p))
			continue;

		if (!gui::Config::aimAtFriendly)
			if (p->iTeamNum == localEnt->iTeamNum)
				continue;

		if (!gui::Config::aimAtEnemy)
			if (p->iTeamNum != localEnt->iTeamNum)
				continue;

		Vector3 vecViewOffset = p->vecViewOffset;
		Vector3 entPos = p->vecOrigin;

		Vector3 pos = entPos + vecViewOffset;

		int boneID = 8;

		if (gui::Config::aimbotListBoneID == 0)
			boneID = 8;
		else if (gui::Config::aimbotListBoneID == 1)
			boneID = 7;
		else if (gui::Config::aimbotListBoneID == 2)
			boneID = 6;
		else if (gui::Config::aimbotListBoneID == 3)
			boneID = 3;

		Engine::AimAt(localEnt, Engine::GetBonePos(p, boneID));
	}
}

void Hack::BHop() {
	if (!gui::Config::bhopOn)
		return;

	if (GetAsyncKeyState(VK_SPACE))
		Engine::Jump(localEnt);
}

void Hack::TriggerBot() {
	if (!gui::Config::triggerBotOn)
		return;

	Ent* p = entList->ents[localEnt->m_iCrosshairId - 1].ent;

	if (!Engine::CheckValidEnt(localEnt, p))
		return;

	if (!gui::Config::triggerTargetFriendly)
		if (p->iTeamNum == localEnt->iTeamNum)
			return;

	if (!gui::Config::triggerTargetEnemy)
		if (p->iTeamNum != localEnt->iTeamNum)
			return;

	// std::this_thread::sleep_for(std::chrono::milliseconds(gui::Config::triggerDelay));

	Engine::Shoot();
}

void Hack::NoFlash() {
	if (!gui::Config::noFlashOn)
		return;

	if (localEnt->m_flFlashMaxAlpha > 0)
		localEnt->m_flFlashMaxAlpha = 0;
}

void Hack::Init() {
	client = (uintptr_t)GetModuleHandle("client.dll");
	engine = (uintptr_t)GetModuleHandle("engine.dll");
	entList = (EntList*)(client + Offsets::dwEntityList);
	localEnt = entList->ents[0].ent;
}

void Hack::Update() {
	Aimbot();
	BHop();
	TriggerBot();
	NoFlash();
}

Ent* Hack::GetLocalPlayer() {
	return localEnt;
}

EntList* Hack::GetEntityList() {
	return entList;
}