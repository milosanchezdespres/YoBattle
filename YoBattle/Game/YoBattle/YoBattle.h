#pragma once

#include "../../ECS/GameLoop/GameLoop.h"

#include "../../ECS/ECS.h"
using namespace ECS;

class YoBattle : public GameLoop
{
	public:
		YoBattle();

		Entity* test;
		Entity* test2;

		SpriteSystem* sprites;

	protected:
		void OnInit();
		void OnEvent();
		void OnUpdate();
		void OnDraw();
		void OnClose();
};