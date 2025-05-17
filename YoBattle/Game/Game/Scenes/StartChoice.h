#pragma once

#include "../Utils.h"

namespace Games
{
	struct StartChoice : public Scene
	{
		int screen_width, screen_height;

		RaylibHandler* game = nullptr;

		StartChoice() : Scene() {}

		void __OnEnter()
		{
			game->background = WHITE;

			screen_width = game->screen_width();
			screen_height = game->screen_height();

			start<RenderSystem>();

			sys<RenderSystem>()->game = game;
		}

		void __OnEvents()
		{
			//...
		}

		void __OnUpdate()
		{
			//...
		}

		void __OnLastUpdate()
		{
			//...
		}

		void __OnDraw()
		{
			sys<RenderSystem>()->update(0);
		}

		void __OnExit()
		{
			//...
		}
	};
}