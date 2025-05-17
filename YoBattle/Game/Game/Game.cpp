#include "Game.h"

namespace Games
{
	Game::Game(string title) : RaylibHandler(title) { }

	void Game::OnInit()
	{
		load_texture("spirikat");
		//...

		load_scene<Scene>();
		//...

		go_to<Scene>();

		//this will normally be inside a class that herits from scene
		//for test purposes//
		scene()->start<RenderSystem>();
		scene()->sys<RenderSystem>()->game = this;
		scene()->add<Entity>("test");
		scene()->entity<Entity>("test")->attach<Sprite>("sprite1");
		scene()->component<Sprite>("test", "sprite1")->texture = "spirikat";
		scene()->component<Sprite>("test", "sprite1")->x = 130;
		scene()->component<Sprite>("test", "sprite1")->y = 130;
		scene()->component<Sprite>("test", "sprite1")->scale = 2;
		scene()->upload<RenderSystem, Sprite>("test", "sprite1");
		//...
	}

	void Game::OnUpdate(float delta)
	{
		scene()->Update(delta);
	}

	void Game::OnDraw()
	{
		//scene()->sys<RenderSystem>()->update(0);
	}
}