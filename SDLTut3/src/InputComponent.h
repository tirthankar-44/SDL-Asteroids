#pragma once

#include <cstdint>

#include "MoveComponent.h"

class InputComponent: public MoveComponent {
public:
	InputComponent(class Actor* owner);

	void ProcessInput(const uint8_t* keyState) override;

	float GetMaxForwardSpeed() const { return m_MaxForwardSpeed; }
	void SetMaxForwardSpeed(float forwardSpeed) { m_MaxForwardSpeed = forwardSpeed; }

	float GetMaxAngularSpeed() const { return m_MaxAngularSpeed; }
	void SetMaxAngularSpeed(float angularSpeed) { m_MaxAngularSpeed = angularSpeed; }

	int GetForwardKey() const { return m_ForwardKey; }
	void SetForwardKey(int forwardKey) { m_ForwardKey = forwardKey; }

	int GetBackKey() const { return m_BackKey; }
	void SetBackKey(int backKey) { m_BackKey = backKey; }

	int GetClockwiseKey() const { return m_ClockwiseKey; }
	void SetClockwiseKey(int clockwiseKey) { m_ClockwiseKey = clockwiseKey; }

	int GetCounterClockwiseKey() const { return m_CounterClockwiseKey; }
	void SetCounterClockwiseKey(int counterClockwiseKey) { m_CounterClockwiseKey = counterClockwiseKey; }

private:
	float m_MaxForwardSpeed;
	float m_MaxAngularSpeed;

	int m_ForwardKey;
	int m_BackKey;

	int m_ClockwiseKey;
	int m_CounterClockwiseKey;
};