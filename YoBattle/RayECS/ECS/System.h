#pragma once

#include "Utils.h"

namespace ECS
{
	struct BaseSystem
	{
		bool standalone;

		vector<Component*> components;

		BaseSystem() { standalone = false; }

		virtual ~BaseSystem() = default;

		virtual void update(float delta) {}
	};

	template <typename T>
	struct System : public BaseSystem
	{
		System() : BaseSystem() {}

		void upload(Component* component) { components.push_back(component); }
	};
}