#pragma once

#include <vector>

#include "Math.h"

class Actor {
public:
	enum State {
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState);

	const Vector2& GetPosition() const { return m_Position; }
	void SetPosition(const Vector2& pos) { m_Position = pos; }

	float GetScale() const { return m_Scale; }
	void SetScale(float scale) { m_Scale = scale; }

	float GetRotation() const { return m_Rotation; }
	void SetRotation(float rotation) { m_Rotation = rotation; }

	Vector2 GetForward() const { return Vector2(Math::Cos(m_Rotation), -Math::Sin(m_Rotation)); }

	State GetState() const { return m_State; }
	void SetState(State state) { m_State = state; }

	class Game* GetGame() { return m_Game; }

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	State m_State;

	Vector2 m_Position;
	float m_Scale;
	float m_Rotation;

	std::vector<class Component*> m_Components;
	class Game* m_Game;
};

