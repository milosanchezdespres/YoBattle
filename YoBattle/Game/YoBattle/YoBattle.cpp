#include "YoBattle.h"
#include "../../Game/Entities/Character.h"

YoBattle::YoBattle() : GameLoop("YoBattle") {}

void YoBattle::OnInit()
{
	load_texture("spirikat");
	//...

	scene = new Scene();
	scene->add(new DebugSystem());

	scene->push("test", new Character(scene, "spirikat", 56, 3, 300));
	scene->entity<Character>("test")->component<Axis>()->x = 1;
	scene->entity<Character>("test")->component<Axis>()->y = 1;

	scene->push("test2", new Character(scene, "spirikat", 56, 3, 300));
	scene->entity<Character>("test2")->component<Axis>()->x = 0;
	scene->entity<Character>("test2")->component<Axis>()->y = 1;

	scene->push("test3", new Character(scene, "spirikat", 56, 3, 300));
	scene->entity<Character>("test3")->component<Axis>()->x = 1;
	scene->entity<Character>("test3")->component<Axis>()->y = 0;
}

void YoBattle::OnEvent()
{
	//...
}

void YoBattle::OnUpdate()
{
	//...
	scene->update(GetFrameTime());
}

void YoBattle::OnDraw()
{
	//...
	scene->draw(this);
}

void YoBattle::OnClose()
{
	//...
	unload_texture("spirikat");
}
