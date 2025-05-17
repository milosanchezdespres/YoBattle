#pragma once

#include "Sprite.h"
#include "../../RayECS/Window/RaylibHandler.h"
using namespace ECS;

class RaylibHandler;

struct RenderSystem : public System<Sprite>
{
	RaylibHandler* game = nullptr;

	RenderSystem() : System() { standalone = true; game = nullptr; }

	RenderSystem(RaylibHandler* _game) : System()
	{
		game = _game;
		standalone = true;
	}

	void update(float delta) override
	{
		for (Component* comp : components)
		{
			Sprite* sprite = dynamic_cast<Sprite*>(comp);
			game->blit(sprite);
		}
	}
};