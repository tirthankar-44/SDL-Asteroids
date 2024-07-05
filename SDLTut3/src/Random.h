#pragma once

#include <random>

#include "Math.h"

class Random {
public:
	static void Init();
	static void Seed(unsigned int seed);

	static float GetFloat();

	static float GetFloatRange(float min, float max);

	static int GetIntRange(int min, int max);

	static Vector2 GetVector2(const Vector2& min, const Vector2& max);
	static Vector3 GetVector3(const Vector3& min, const Vector3& max);

private:
	static std::mt19937 m_SGenerator;
};