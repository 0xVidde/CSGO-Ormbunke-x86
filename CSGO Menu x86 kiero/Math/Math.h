#pragma once

#include "ViewMatrix.h"
#include "Vector4.h"
#include "Vector3.h"
#include "Vector2.h"

#define ABS(x) ((x < 0) ? (-x) : (x))
#define PI 3.14159265358

namespace Math
{
	bool WorldToScreen(Vector3 pos, Vector2& screen, float viewMatrix[16], Vector2 windowDim);
	Vector2 CalcAngle(Vector3 src, Vector3 dst);

	float DegreeToRadian(float degree);
	Vector3 DegreeToRadian(Vector3 degrees);
};

