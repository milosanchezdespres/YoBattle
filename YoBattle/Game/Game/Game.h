#pragma once

#include "../Utils.h"

namespace Games
{
	class Game : public RaylibHandler
	{
		public:
			Game(string title);

			//...
			Scene* test;

		protected:
			void OnInit();
			void OnUpdate(float delta);
			void OnDraw();
	};
}