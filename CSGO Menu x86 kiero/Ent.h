#pragma once

#include "Offsets.h"
#include "Math/Math.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

class Ent
{
public:
	union {
		DEFINE_MEMBER_N(bool, isDormant, Offsets::m_bDormant);
		// iHealth
		DEFINE_MEMBER_N(int, iHealth, Offsets::m_iHealth);
		// vecOrigin
		DEFINE_MEMBER_N(Vector3, vecOrigin, Offsets::m_vecOrigin);
		// View Offset
		DEFINE_MEMBER_N(Vector3, vecViewOffset, Offsets::m_vecViewOffset);
		// iTeamNum
		DEFINE_MEMBER_N(int, iTeamNum, Offsets::m_iTeamNum);
		// boneMatrix
		DEFINE_MEMBER_N(int, boneMatrix, Offsets::m_dwBoneMatrix);
		// ArmorValue
		DEFINE_MEMBER_N(int, ArmorValue, Offsets::m_ArmorValue);
		// m_fFlags
		DEFINE_MEMBER_N(int, m_fFlags, Offsets::m_fFlags);
		// aimPunchAngle
		DEFINE_MEMBER_N(Vector3, aimPunchAngle, Offsets::m_aimPunchAngle);
		// m_iCrosshairId
		DEFINE_MEMBER_N(int, m_iCrosshairId, Offsets::m_iCrosshairId);
		// m_iDefaultFOV
		DEFINE_MEMBER_N(int, m_iDefaultFOV, Offsets::m_iDefaultFOV);
		// m_flFlashMaxAlpha
		DEFINE_MEMBER_N(float, m_flFlashMaxAlpha, Offsets::m_flFlashMaxAlpha);
		// m_iObserverMode
		DEFINE_MEMBER_N(int, m_iObserverMode, Offsets::m_iObserverMode);
		// m_bIsDefusing
		DEFINE_MEMBER_N(bool, m_bIsDefusing, Offsets::m_bIsDefusing);
		// m_iGlowIndex
		DEFINE_MEMBER_N(int, m_iGlowIndex, Offsets::m_iGlowIndex);
	};
};

class EntListObj {
public:
	Ent* ent;
	char padding[12];
};

class EntList {
public:
	EntListObj ents[32];
};