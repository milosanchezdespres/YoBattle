#include "YoBattle.h"

YoBattle::YoBattle() : GameLoop("YoBattle") {}

void YoBattle::OnInit()
{
	load_texture("spirikat");

	//...
	test = new Entity();
	test->push(new Sprite("spirikat", 150, 150, 2, 56, 0));
}

void YoBattle::OnEvent()
{
	//...
}

void YoBattle::OnUpdate()
{
	//...
}

void YoBattle::OnDraw()
{
	//...
	blit(test->component<Sprite>());
}

void YoBattle::OnClose()
{
	//...
	unload_texture("spirikat");
}
