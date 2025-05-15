#include "YoBattle.h"
#include "../../Game/Entities/Character.h"

YoBattle::YoBattle() : GameLoop("YoBattle") {}

void YoBattle::OnInit()
{
	load_texture("spirikat");
	//...

	scene = new Scene();
	scene->add(new SpriteSystem());
	scene->add(new DebugSystem());

	scene->push("test", new Character(scene, "spirikat", 56, 3, 150));
	scene->entity<Character>("test")->component<Axis>()->x = 1;
	scene->entity<Character>("test")->component<Axis>()->y = 1;
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
