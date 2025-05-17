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

	struct Sprite : public Component
	{
		float x, y;
		int size, tile_index;
		string texture;
		bool visible;

		Sprite() : Component()
		{
			x = 0;
			y = 0;

			tile_index = 0;
			size = 8;

			texture = "";

			visible = true;
		}
	};

	struct RenderSystem : public System<Sprite>
	{
		RenderSystem() : System() { standalone = true; }

		void update(float delta) override
		{
			for (auto it = components.begin(); it != components.end(); ++it)
			{
				Component* c = *it;
				cout << c->parent->alias << endl;
			}
		}
	};
}