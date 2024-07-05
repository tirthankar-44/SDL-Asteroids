#pragma once

#include "Component.h"
#include "Math.h"

class CircleComponent : public Component {
public:
	CircleComponent(class Actor* owner);
	
	void SetRadius(float radius) { m_Radius = radius; }
	float GetRadius() const;

	const Vector2& GetCenter() const;

private:
	float m_Radius;
};

inline bool Intersect(CircleComponent& a, CircleComponent& b) {
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}