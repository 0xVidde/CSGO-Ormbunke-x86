#include "gui.h"

#include <Windows.h>

#include "Includes/imgui/imgui.h"
#include "Includes/imgui/imgui_impl_win32.h"
#include "Includes/imgui/imgui_impl_dx9.h"

#include <WinUser.h>
#include "Hack.h"

#include "Utils.h"
#include "Engine.h"

#include "Drawing.h"

void gui::RenderMain() {
	if (GetAsyncKeyState(VK_HOME) & 1)
		showMenu = !showMenu;

	if (!showMenu)
		return;

	ImGui::Begin("Ormbunke x86");

	ImGui::BeginTabBar("Cheats");

	if (ImGui::BeginTabItem("Aimbot")) {
		ImGui::Checkbox("Aimbot", &gui::Config::aimbotOn);
		ImGui::SameLine();
		ImGui::Text(" --  Hold C");

		static const char* bones[]{
			"Head",
			"Neck",
			"Chest",
			"Abdoment"
		};

		ImGui::ListBox("", &gui::Config::aimbotListBoneID, bones, 4);

		ImGui::Spacing();

		ImGui::Separator();

		ImGui::Spacing();

		ImGui::Checkbox("Draw FOV Circle", &gui::Config::drawFOVCircle);
		ImGui::SameLine();
		ImGui::ColorEdit4("...", gui::Config::FOVCircleColor);

		ImGui::SliderFloat("Aimbot FOV Value", &gui::Config::fov_value, 1, 180);

		ImGui::Spacing();

		ImGui::Separator();

		ImGui::Spacing();

		ImGui::Checkbox("Target Team", &gui::Config::aimAtFriendly);
		ImGui::Checkbox("Target Enemy", &gui::Config::aimAtEnemy);

		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Trigger Bot")) {
		ImGui::Checkbox("Toggle Trigger Bot", &gui::Config::triggerBotOn);
		ImGui::Checkbox("Target Team", &gui::Config::triggerTargetFriendly);
		ImGui::Checkbox("Target Enemies", &gui::Config::triggerTargetEnemy);

		ImGui::Spacing();

		ImGui::Separator();

		ImGui::Spacing();

		// ImGui::SliderInt("Reaction Delay", &gui::Config::triggerDelay, 1, 300);

		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Visuals")) {
		ImGui::Checkbox("Toggle ESP", &gui::Config::espON);

		ImGui::Spacing();

		ImGui::Separator();

		ImGui::Spacing();

		ImGui::Checkbox("Draw Tracers", &gui::Config::drawTracers);

		static const char* tracer_modes[]{
			"Top",
			"Center",
			"Bottom",
		};

		ImGui::ListBox("Tracer Point", &gui::Config::tracerPosIndex, tracer_modes, 3);

		ImGui::Checkbox("Draw Team Tracer", &gui::Config::drawTracerFriendly);

		ImGui::Checkbox("Draw Enemy Tracer", &gui::Config::drawTracerEnemy);

		ImGui::Spacing();

		ImGui::Text("Tracer Near Distance");
		ImGui::SliderFloat("Tracer Near Distance", &gui::Config::tracerNear, 1, 1000);

		ImGui::Spacing();

		ImGui::Separator();

		ImGui::Checkbox("Draw 2D Box", &gui::Config::draw2DBox);

		ImGui::Checkbox("Draw Team Box", &gui::Config::drawBoxFriendly);

		ImGui::Checkbox("Draw Enemy Box", &gui::Config::drawBoxEnemy);

		ImGui::Spacing();

		ImGui::Text("Tracer 2D Box Distance");
		ImGui::SliderFloat("", &gui::Config::boxNear, 1, 1000);

		ImGui::Spacing();

		ImGui::Separator();

		ImGui::Spacing();

		ImGui::EndTabItem();
	}

	if (ImGui::BeginTabItem("Misc")) {
		ImGui::Checkbox("Toggle B-Hop", &gui::Config::bhopOn);
		ImGui::Checkbox("Toggle No Flash", &gui::Config::noFlashOn);

		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();

	ImGui::End();
}

void gui::ESPMain() {
	Vector2 windowDim = Utils::GetWindowRes();
	ViewMatrix viewMatrix = Engine::GetViewMatrix();

	Ent* localPlayer = Hack::GetLocalPlayer();
	EntList* entList = Hack::GetEntityList();

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(windowDim.x, windowDim.y));
	ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);

	auto pDrawList = ImGui::GetWindowDrawList();

	if (gui::Config::drawFOVCircle) {
		float rad = tanf(Math::DegreeToRadian(gui::Config::fov_value) / 2) / tanf(Math::DegreeToRadian(localPlayer->m_iDefaultFOV) / 2) * windowDim.x;
		pDrawList->AddCircle(ImVec2(windowDim.x / 2, windowDim.y / 2), rad, 
			ImColor(gui::Config::FOVCircleColor[0],
				gui::Config::FOVCircleColor[1],
				gui::Config::FOVCircleColor[2],
				gui::Config::FOVCircleColor[3]), 100);
	}

	for (size_t i = 0; i < Engine::GetMaxPlayers(); i++)
	{
		if (!gui::Config::espON)
			continue;

		Ent* player = entList->ents[i].ent;

		if (!Engine::CheckValidEnt(localPlayer, player))
			continue;

		Vector2 feetPos;
		if (!Math::WorldToScreen(player->vecOrigin, feetPos, viewMatrix.matrix, windowDim))
			continue;

		Vector2 headPos;
		Vector3 pHeadPos = Engine::GetBonePos(player, 8);
		if (!Math::WorldToScreen(pHeadPos, headPos, viewMatrix.matrix, windowDim))
			continue;

		if (gui::Config::draw2DBox && Engine::GetBonePos(localPlayer, 8).Distance(pHeadPos) > gui::Config::boxNear) {
			if (gui::Config::drawBoxFriendly)
				if (player->iTeamNum == localPlayer->iTeamNum)
					DrawHack2DBox(headPos, feetPos, headPos.Distance(feetPos), 1, ImColor(gui::Config::friendlyColor[0],
						gui::Config::friendlyColor[1],
						gui::Config::friendlyColor[2],
						gui::Config::friendlyColor[3]));

			if (gui::Config::drawBoxEnemy)
				if (player->iTeamNum != localPlayer->iTeamNum)
					DrawHack2DBox(headPos, feetPos, headPos.Distance(feetPos), 1, ImColor(gui::Config::enemyColor[0],
						gui::Config::enemyColor[1],
						gui::Config::enemyColor[2],
						gui::Config::enemyColor[3]));
		}

		if (gui::Config::drawTracers && Engine::GetBonePos(localPlayer, 8).Distance(pHeadPos) > gui::Config::tracerNear) {

			ImVec2 tracerPos = ImVec2(windowDim.x / 2, windowDim.y);

			if (gui::Config::tracerPosIndex == 0)
				tracerPos = ImVec2(windowDim.x / 2, 1);
			else if (gui::Config::tracerPosIndex == 1)
				tracerPos = ImVec2(windowDim.x / 2, windowDim.y / 2);
			else if (gui::Config::tracerPosIndex == 2)
				tracerPos = ImVec2(windowDim.x / 2, windowDim.y);

			if (gui::Config::drawTracerFriendly)
				if (player->iTeamNum == localPlayer->iTeamNum)
					pDrawList->AddLine(tracerPos, ImVec2(feetPos.x, feetPos.y), ImColor(gui::Config::friendlyColor[0],
						gui::Config::friendlyColor[1],
						gui::Config::friendlyColor[2],
						gui::Config::friendlyColor[3]));

			if (gui::Config::drawTracerEnemy)
				if (player->iTeamNum != localPlayer->iTeamNum)
					pDrawList->AddLine(tracerPos, ImVec2(feetPos.x, feetPos.y), ImColor(gui::Config::enemyColor[0],
						gui::Config::enemyColor[1],
						gui::Config::enemyColor[2],
						gui::Config::enemyColor[3]));
		}
	}
	ImGui::End();
}