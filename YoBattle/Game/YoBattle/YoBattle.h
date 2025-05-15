#pragma once

#include "../../ECS/GameLoop/GameLoop.h"
#include "../../ECS/ECS.h"
#include "../Components/Debug.h"

using namespace ECS;

class YoBattle : public GameLoop
{
	public:
		YoBattle();

		Scene* scene;

		//Entity* test;
		//Entity* test2;
		//Entity* test3;

		//SpriteSystem* sprites;
		//DebugSystem* messages;

	protected:
		void OnInit();
		void OnEvent();
		void OnUpdate();
		void OnDraw();
		void OnClose();
};