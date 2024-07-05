#pragma once

#include <SDL.h>

#include "Component.h"

class SpriteComponent : public Component {
public:
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return m_DrawOrder; }
	int GetTexHeight() const { return m_TextureHeight; }
	int GetTexWidth() const { return m_TextureWidth; }

protected:
	SDL_Texture* m_Texture;
	int m_DrawOrder;
	int m_TextureWidth;
	int m_TextureHeight;
};

