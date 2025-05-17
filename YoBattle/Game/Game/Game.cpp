#include "Game.h"

namespace Games
{
	Game::Game(string title) : RaylibHandler(title) { }

	void Game::OnInit()
	{
		//...

		load_texture("spirikat");

		test = new Scene();
		test->start<RenderSystem>();
		test->sys<RenderSystem>()->game = this;

		test->add<Entity>("test");
		test->entity<Entity>("test")->attach<Sprite>("sprite1");
		test->entity<Entity>("test")->attach<Sprite>("sprite2");

		test->upload<RenderSystem, Sprite>("test", "sprite1");
		test->upload<RenderSystem, Sprite>("test", "sprite2");

		test->component<Sprite>("test", "sprite1")->texture = "spirikat";
		test->component<Sprite>("test", "sprite1")->x = 130;
		test->component<Sprite>("test", "sprite1")->y = 130;
		test->component<Sprite>("test", "sprite1")->scale = 2;

		test->component<Sprite>("test", "sprite2")->texture = "spirikat";
		test->component<Sprite>("test", "sprite2")->scale = 2;
	}

	void Game::OnUpdate(float delta)
	{
		//...

		test->Update(delta);
	}

	void Game::OnDraw()
	{
		//...
		test->sys<RenderSystem>()->update(0);
	}
}