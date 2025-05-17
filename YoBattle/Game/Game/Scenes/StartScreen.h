#pragma once

#include "../Utils.h"

namespace Games
{
	struct StartScreen : public Scene
	{
		int screen_width, screen_height;

		RaylibHandler* game = nullptr;

		StartScreen() : Scene() {}

		void __OnEnter()
		{
			game->background = BLACK;

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

			game->write("press start", 32, (screen_width / 2) - 100, (screen_height / 2) + 148, WHITE);
		}

		void __OnExit()
		{
			//...
		}
	};
}