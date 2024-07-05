#include <algorithm>
#include <iostream>

#include <SDL_image.h>

#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Random.h"

Game::Game() :
	m_Window(nullptr),
	m_Renderer(nullptr),
	m_IsRunning(true),
	m_UpdatingActors(false) {

}

bool Game::Initialize() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		std::cout << "Error initializing SDL: " << SDL_GetError();
		return false;
	}

	m_Window = SDL_CreateWindow("My Game Structure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	if (!m_Window) {
		std::cout << "Error creating window: " << SDL_GetError();
		return false;
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_Renderer) {
		std::cout << "Error creating Renderer: " << SDL_GetError();
		return false;
	}

	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cout << "Error initializing SDL_image: " << SDL_GetError();
		return false;
	}

	Random::Init();

	LoadData();

	m_TicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop() {
	while (m_IsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			m_IsRunning = false;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	if (keyState[SDL_SCANCODE_ESCAPE]) {
		m_IsRunning = false;
	}

	m_UpdatingActors = true;
	for (auto actor : m_Actors) {
		actor->ProcessInput(keyState);
	}
	m_UpdatingActors = false;
}

void Game::UpdateGame() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_TicksCount + 16));

	float deltaTime = (SDL_GetTicks() - m_TicksCount) / 1000.0f;

	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	m_TicksCount = SDL_GetTicks();

	m_UpdatingActors = true;

	for (auto actor : m_Actors) {
		actor->Update(deltaTime);
	}

	m_UpdatingActors = false;

	for (auto pending : m_PendingActors) {
		m_Actors.emplace_back(pending);
	}
	m_PendingActors.clear();

	std::vector<Actor*> deadActors;
	for (auto actor : m_Actors) {
		if (actor->GetState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors) {
		delete actor;
	}

}

void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(m_Renderer, 220, 220, 220, 255);
	SDL_RenderClear(m_Renderer);

	for (auto sprite : m_Sprites) {
		sprite->Draw(m_Renderer);
	}

	SDL_RenderPresent(m_Renderer);
}

void Game::LoadData() {
	m_Ship = new Ship(this);
	m_Ship->SetPosition(Vector2(512.0f, 384.0f));
	m_Ship->SetRotation(Math::PiOver2);

	const int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; ++i) {
		new Asteroid(this);
	}
}

void Game::UnloadData() {
	while (!m_Actors.empty()) {
		delete m_Actors.back();
	}

	for (auto i : m_Textures) {
		SDL_DestroyTexture(i.second);
	}
	m_Textures.clear();
}

SDL_Texture* Game::GetTexture(const std::string& fileName) {
	SDL_Texture* tex = nullptr;

	auto iter = m_Textures.find(fileName);
	if (iter != m_Textures.end()) {
		tex = iter->second;
	}

	else {
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf) {
			std::cout << "Error loading texture: " << IMG_GetError() << "\n";
			return nullptr;
		}

		else {
			tex = SDL_CreateTextureFromSurface(m_Renderer, surf);
			SDL_FreeSurface(surf);

			if (!tex) {
				std::cout << "Error converting surface to texture: " << SDL_GetError() << "\n";
				return nullptr;
			}

			m_Textures.emplace(fileName.c_str(), tex);
		}
	}

	return tex;
}

void Game::AddAsteroid(Asteroid* ast) {
	m_Asteroids.emplace_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast) {
	auto iter = std::find(m_Asteroids.begin(), m_Asteroids.end(), ast);
	if (iter != m_Asteroids.end()) {
		m_Asteroids.erase(iter);
	}
}

void Game::AddActor(Actor* actor) {
	if (m_UpdatingActors) {
		m_PendingActors.emplace_back(actor);
	}

	else {
		m_Actors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor) {
	auto iter = std::find(m_PendingActors.begin(), m_PendingActors.end(), actor);
	if (iter != m_PendingActors.end()) {
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, m_PendingActors.end() - 1);
		m_PendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(m_Actors.begin(), m_Actors.end(), actor);
	if (iter != m_Actors.end()) {
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, m_Actors.end() - 1);
		m_Actors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite) {
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = m_Sprites.begin();
	for (; iter != m_Sprites.end(); ++iter) {
		if (myDrawOrder < (*iter)->GetDrawOrder()) {
			break;
		}
	}

	m_Sprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite) {
	auto iter = std::find(m_Sprites.begin(), m_Sprites.end(), sprite);
	m_Sprites.erase(iter);
}

void Game::Shutdown() {
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}