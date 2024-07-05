#include "Asteroid.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game) :
	Actor(game),
	m_Circle(nullptr) {
	Vector2 randomPos = Random::GetVector2(Vector2::Zero, Vector2(1024.0f, 768.0f));
	SetPosition(randomPos);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("assets/Asteroid.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	m_Circle = new CircleComponent(this);
	m_Circle->SetRadius(40.0f);

	game->AddAsteroid(this);
}

Asteroid::~Asteroid() {
	GetGame()->RemoveAsteroid(this);
}