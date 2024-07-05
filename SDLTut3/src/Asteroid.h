#pragma once

#include "Actor.h"

class Asteroid :public Actor {
public:
	Asteroid(class Game* game);
	~Asteroid();

	class CircleComponent* GetCircle() const { return m_Circle; }

private:
	class CircleComponent* m_Circle;
};