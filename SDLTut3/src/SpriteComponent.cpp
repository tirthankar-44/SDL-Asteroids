#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

#include <iostream>

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder) :
	Component(owner),
	m_DrawOrder(drawOrder),
	m_TextureWidth(0),
	m_TextureHeight(0) {
	m_Owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
	m_Owner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer) {
	if (m_Texture) {
		SDL_Rect r;
		r.w = static_cast<int>(m_TextureWidth * m_Owner->GetScale());
		r.h = static_cast<int>(m_TextureHeight * m_Owner->GetScale());

		r.x = static_cast<int>(m_Owner->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(m_Owner->GetPosition().y - r.h / 2);

		SDL_RenderCopyEx(renderer, m_Texture, nullptr, &r, -Math::ToDegrees(m_Owner->GetRotation()), nullptr, SDL_FLIP_NONE);
	}
	else {
		std::cout << "Unable to draw\n";
	}
}

void SpriteComponent::SetTexture(SDL_Texture* texture) {
	m_Texture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &m_TextureWidth, &m_TextureHeight);
}