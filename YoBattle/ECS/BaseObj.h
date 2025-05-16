#pragma once

#include "Utils.h"

namespace ECS
{
	struct BaseObj
	{
		int ID;
		string alias;
		BaseObj* parent;

		BaseObj()
		{
			ID = -1;
			alias = "unnamed";
			parent = nullptr;
		}
	};
}