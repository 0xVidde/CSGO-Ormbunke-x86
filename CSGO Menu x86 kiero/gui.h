#pragma once

#include "Includes/imgui/imgui.h"

namespace gui
{
	inline bool showMenu = false;

	void RenderMain();
	void ESPMain();

	namespace Config {
#pragma region Aimbot
		inline bool aimbotOn = false;
		inline int aimbotListBoneID = 8;

		inline bool drawFOVCircle = false;
		static inline float FOVCircleColor[4] = { 1.f, 1.f, 1.f, 1.f };
		inline float fov_value = 10;

		inline bool aimAtEnemy = false;
		inline bool aimAtFriendly = false;
#pragma endregion



#pragma region TriggerBot
		inline bool triggerBotOn = false;
		// inline int triggerDelay = 40;
		inline bool triggerTargetEnemy = false;
		inline bool triggerTargetFriendly = false;
#pragma endregion



#pragma region Misc
		inline bool bhopOn = false;
		inline bool noFlashOn = false;
#pragma endregion




#pragma region ESP
		inline bool espON = false;
		static inline float friendlyColor[] = { 0, 0, 1.f, 1.f };
		static inline float enemyColor[] = { 1.f, 0, 0, 1.f };


		inline bool drawTracers = false;
		inline int tracerPosIndex = 0;
		inline bool drawTracerFriendly = false;
		inline bool drawTracerEnemy = false;
		inline float tracerNear = 4;


		inline bool draw2DBox = false;
		inline bool drawBoxFriendly = false;
		inline bool drawBoxEnemy = false;
		inline float boxNear = 40;
#pragma endregion
	}
};

