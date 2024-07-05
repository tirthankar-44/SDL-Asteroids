#include "Random.h"

void Random::Init() {
	std::random_device rd;
	Random::Seed(rd());
}

void Random::Seed(unsigned int seed) {
	m_SGenerator.seed(seed);
}

float Random::GetFloat() {
	return GetFloatRange(0.0f, 1.0f);
}

float Random::GetFloatRange(float min, float max) {
	std::uniform_real_distribution<float> dist(min, max);
	return dist(m_SGenerator);
}

int Random::GetIntRange(int min, int max) {
	std::uniform_int_distribution<int> dist(min, max);
	return dist(m_SGenerator);
}

Vector2 Random::GetVector2(const Vector2& min, const Vector2& max) {
	Vector2 r = Vector2(GetFloat(), GetFloat());
	return min + (max - min) * r;
}

Vector3 Random::GetVector3(const Vector3& min, const Vector3& max) {
	Vector3 r = Vector3(GetFloat(), GetFloat(), GetFloat());
	return min + (max - min) * r;
}

std::mt19937 Random::m_SGenerator;