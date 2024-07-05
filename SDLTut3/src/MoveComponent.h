#pragma once

#include "Component.h"

class MoveComponent :public Component {
public:
	MoveComponent(class Actor* owner, int updateOrder = 10);
	
	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return m_AngularSpeed; }
	void SetAngularSpeed(float angularSpeed) { m_AngularSpeed = angularSpeed; }

	float GetForwardSpeed() const { return m_ForwardSpeed; }
	void SetForwardSpeed(float forwardSpeed) { m_ForwardSpeed = forwardSpeed; }

private:
	float m_AngularSpeed;
	float m_ForwardSpeed;
};