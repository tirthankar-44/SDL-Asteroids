#include "Ship.h"
#include "SpriteComponent.h"
#include "InputComponent.h"
#include "Game.h"
#include "Laser.h"

#include <iostream>

Ship::Ship(Game* game) :
	Actor(game),
	m_LaserCooldown(0.0f) {
	SpriteComponent* sc = new SpriteComponent(this, 150);
	sc->SetTexture(game->GetTexture("assets/Ship.png"));

	InputComponent* ic = new InputComponent(this);
	ic->SetForwardKey(SDL_SCANCODE_UP);
	ic->SetBackKey(SDL_SCANCODE_DOWN);
	ic->SetClockwiseKey(SDL_SCANCODE_LEFT);
	ic->SetCounterClockwiseKey(SDL_SCANCODE_RIGHT);
	ic->SetMaxForwardSpeed(300.0f);
	ic->SetMaxAngularSpeed(Math::TwoPi);
}

void Ship::UpdateActor(float deltaTime) {
	m_LaserCooldown -= deltaTime;
}

void Ship::ActorInput(const uint8_t* keyState) {
	if (keyState[SDL_SCANCODE_SPACE] && m_LaserCooldown <= 0.0f) {
		Laser* laser = new Laser(GetGame());
		
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		std::cout << "Laser was shot, Position: " << laser->GetPosition().x << ", " << laser->GetPosition().y << "\n";

		m_LaserCooldown = 0.5f;
	}
}