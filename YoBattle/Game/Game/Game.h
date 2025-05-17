#pragma once

#include "Utils.h"

namespace Games
{
	class Game : public RaylibHandler
	{
		public:
			Game(string title);

		protected:
			void OnInit();
			void OnEvent();
			void OnUpdate(float delta);
			void OnDraw();
	};
}