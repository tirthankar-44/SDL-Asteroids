#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner, int updateOrder) :
	Component(owner, updateOrder),
	m_AngularSpeed(0.0f),
	m_ForwardSpeed(0.0f) {

}

void MoveComponent::Update(float deltaTime) {
	if (!Math::NearZero(m_AngularSpeed)) {
		float rot = m_Owner->GetRotation();
		rot += m_AngularSpeed * deltaTime;
		m_Owner->SetRotation(rot);
	}

	if (!Math::NearZero(m_ForwardSpeed)) {
		Vector2 pos = m_Owner->GetPosition();
		pos += m_Owner->GetForward() * m_ForwardSpeed * deltaTime;

		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }

		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		m_Owner->SetPosition(pos);
	}
}
