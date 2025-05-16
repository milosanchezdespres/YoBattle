#pragma once

#include "../ECS/Component.h"

namespace ECS
{
	struct DebugComponent : public Component
	{
		float x, y;

		DebugComponent() : Component()
		{
			x = 0;
			y = 0;
		}

		void OnJson() override
		{
			__json["x"] = x;
			__json["y"] = y;
		}

		void OnLoad() override
		{
			x = __json["x"];
			y = __json["y"];
		}
	};
}