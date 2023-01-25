#include "Drawing.h"

void DrawHack2DBox(Vector2 top, Vector2 bot, int height, int thickness, ImColor color)
{
	auto pDrawList = ImGui::GetWindowDrawList();

	Vector2 tl, tr;
	tl.x = top.x - height / 4;
	tr.x = top.x + height / 4;
	tl.y = tr.y = top.y;

	Vector2 bl, br;
	bl.x = bot.x - height / 4;
	br.x = bot.x + height / 4;
	bl.y = br.y = bot.y;

	// pDrawList->AddLine(ImVec2(tl.x, tl.y), ImVec2(tr.x, tr.y), ImColor(255, 255, 255), 1);
	pDrawList->AddLine(ImVec2(tl.x, tl.y), ImVec2(tr.x, tr.y), color, thickness);
	pDrawList->AddLine(ImVec2(bl.x, bl.y), ImVec2(br.x, br.y), color, thickness);
	pDrawList->AddLine(ImVec2(tl.x, tl.y), ImVec2(bl.x, bl.y), color, thickness);
	pDrawList->AddLine(ImVec2(tr.x, tr.y), ImVec2(br.x, br.y), color, thickness);
}