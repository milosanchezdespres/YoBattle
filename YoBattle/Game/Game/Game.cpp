#include "Game.h"

namespace Games
{
	Game::Game(string title) : RaylibHandler(title) { }

	void Game::OnInit()
	{
		load_texture("spirikat");
		//...

		load_scene<StartScreen>();
		scene<StartScreen>()->game = this;
		//...

		go_to<StartScreen>();
	}

	void Game::OnEvent() { scene()->Events(); }

	void Game::OnUpdate(float delta) { scene()->Update(delta); }

	void Game::OnDraw() { scene()->Draw(); }
}