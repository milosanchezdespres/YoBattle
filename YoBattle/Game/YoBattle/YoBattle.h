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

	protected:
		void OnInit();
		void OnEvent();
		void OnUpdate();
		void OnDraw();
		void OnClose();
};