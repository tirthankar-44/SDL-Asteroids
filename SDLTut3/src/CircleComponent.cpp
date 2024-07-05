#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner) :
	Component(owner),
	m_Radius(0.0f) {

}

const Vector2& CircleComponent::GetCenter() const {
	return m_Owner->GetPosition();
}

float CircleComponent::GetRadius() const {
	return m_Owner->GetScale() * m_Radius;
}

