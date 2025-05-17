#pragma once

#include "Utils.h"

namespace ECS
{
	struct Component : public BaseObj
	{
		Component() : BaseObj() { }

		virtual ~Component() = default;
	};
}