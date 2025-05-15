#pragma once

#include "../../ECS/ECS.h"
using namespace ECS;

struct Character : public Entity
{
	Character() : Entity() {}

	Character(Scene* scene, string sprite, int size, float scale = 1, float speed = 200) :
		Entity () { OnLoad(scene, vector<any>{sprite, size, scale, speed}); }

    void OnLoad(Scene* scene, vector<any> _load_parameters)
    {
		Entity::OnLoad(scene, _load_parameters);

		push(new Sprite(param<string>(0), 0, 0, param<float>(2), param<int>(1), param<float>(3)));
		push(new Axis(param<float>(3)));
		component<Axis>()->x = 0;
		component<Axis>()->y = 0;
		push(new Debug("hello world"));
		scene->sys<SpriteSystem>()->upload(this);
		scene->sys<DebugSystem>()->upload(this);
    }
};