#include "Math.h"

bool Math::WorldToScreen(Vector3 pos, Vector2& screen, float viewMatrix[16], Vector2 windowDim) {
	Vector4 clipCoords;
	clipCoords.x = pos.x * viewMatrix[0] + pos.y * viewMatrix[1] + pos.z * viewMatrix[2] + viewMatrix[3];
	clipCoords.y = pos.x * viewMatrix[4] + pos.y * viewMatrix[5] + pos.z * viewMatrix[6] + viewMatrix[7];
	clipCoords.z = pos.x * viewMatrix[8] + pos.y * viewMatrix[9] + pos.z * viewMatrix[10] + viewMatrix[11];
	clipCoords.w = pos.x * viewMatrix[12] + pos.y * viewMatrix[13] + pos.z * viewMatrix[14] + viewMatrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowDim.x / 2 * NDC.x) + (NDC.x + windowDim.x / 2);
	screen.y = -(windowDim.y / 2 * NDC.y) + (NDC.y + windowDim.y / 2);
	return true;
}

Vector2 Math::CalcAngle(Vector3 src, Vector3 dst) {
	Vector3 deltaVec = { dst.x - src.x, dst.y - src.y, dst.z - src.z };
	float deltaVecLength = sqrt(deltaVec.x * deltaVec.x + deltaVec.y * deltaVec.y + deltaVec.z * deltaVec.z);

	float pitch = -asin(deltaVec.z / deltaVecLength) * (180 / PI);
	float yaw = atan2(deltaVec.y, deltaVec.x) * (180 / PI);

	return Vector2(pitch, yaw);
}

float Math::DegreeToRadian(float degree)
{
	return degree * (3.14 / 180);
}

Vector3 Math::DegreeToRadian(Vector3 degrees)
{
	Vector3 radians;
	radians.x = degrees.x * (3.14 / 180);
	radians.y = degrees.y * (3.14 / 180);
	radians.z = degrees.z * (3.14 / 180);
	return radians;
}
