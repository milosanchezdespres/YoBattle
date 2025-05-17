#pragma once

#include "../Utils.h"

namespace Games
{
	struct StartScreen : public Scene
	{

		RaylibHandler* game = nullptr;

		StartScreen() : Scene() {}

		void __OnEnter()
		{
			start<RenderSystem>();

			sys<RenderSystem>()->game = game;
			add<Entity>("test");

			entity("test")->attach<Sprite>("sprite1");
			component<Sprite>("test", "sprite1")->texture = "spirikat";
			component<Sprite>("test", "sprite1")->x = 130;
			component<Sprite>("test", "sprite1")->y = 130;
			component<Sprite>("test", "sprite1")->scale = 2;
			upload<RenderSystem, Sprite>("test", "sprite1");
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