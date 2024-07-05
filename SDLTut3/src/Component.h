#pragma once

#include <cstdint>

class Component {
public:
	Component(class Actor* owner, int updateOrder = 100);
	virtual ~Component();
	virtual void Update(float deltaTime);
	virtual void ProcessInput(const uint8_t* keyState){}

	int GetUpdateOrder() const { return m_UpdateOrder; }

protected:
	class Actor* m_Owner;
	int m_UpdateOrder;
};