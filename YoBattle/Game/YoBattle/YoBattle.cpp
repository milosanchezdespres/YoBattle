#include "YoBattle.h"

YoBattle::YoBattle() : GameLoop("YoBattle") {}

void YoBattle::OnInit()
{
	load_texture("spirikat");
	//...

	sprites = new SpriteSystem();

	//...
	test = new Entity();
	test->push(new Sprite("spirikat", 150, 150, 3, 56, 0));
	test->push(new Axis(200));
	test->component<Axis>()->x = 1;
	test->component<Axis>()->y = 1;
	sprites->upload(test->component<Sprite>(), test);

	test2 = new Entity();
	test2->push(new Sprite("spirikat", 150, 150, 3, 56, 0));
	test2->push(new Axis(200));
	test2->component<Axis>()->x = 0;
	test2->component<Axis>()->y = 1;
	sprites->upload(test2->component<Sprite>(), test2);
}

void YoBattle::OnEvent()
{
	//...
}

void YoBattle::OnUpdate()
{
	//...
	sprites->update(GetFrameTime());
}

void YoBattle::OnDraw()
{
	//...
	blit(test->component<Sprite>());
	blit(test2->component<Sprite>());
}

void YoBattle::OnClose()
{
	//...
	unload_texture("spirikat");
}
