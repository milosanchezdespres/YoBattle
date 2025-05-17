#pragma once

#include "Utils.h"

namespace ECS
{
	struct BaseSystem
	{
		vector<Component*> components;

		BaseSystem() {}

		virtual ~BaseSystem() = default;

		virtual void update(float delta) {}
	};

	template <typename T>
	struct System : public BaseSystem
	{
		System() : BaseSystem() {}

		void upload(Component* component) { components.push_back(component); }
	};

	struct Sprite : public Component
	{
		//...

		Sprite() : Component() {}
	};

	struct RenderSystem : public System<Sprite>
	{
		RenderSystem() : System() {}

		void update(float delta) override
		{
			//...
			for (auto it = components.begin(); it != components.end(); ++it)
			{
				Component* c = *it;
				cout << c->parent->alias << endl;
			}
		}
	};
}