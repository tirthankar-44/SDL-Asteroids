#pragma once

#include <unordered_map>
#include <string>
#include <vector>

#include <SDL.h>

class Game {
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const std::string& fileName);

	void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return m_Asteroids; }

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	std::unordered_map<std::string, SDL_Texture*> m_Textures;

	std::vector<class Actor*> m_Actors;
	std::vector<class Actor*> m_PendingActors;

	std::vector<class SpriteComponent*> m_Sprites;

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	Uint32 m_TicksCount;
	
	bool m_IsRunning;
	bool m_UpdatingActors;

	class Ship* m_Ship;
	std::vector<class Asteroid*> m_Asteroids;
};