#include "YoBattle.h"

YoBattle::YoBattle() : GameLoop("YoBattle") {}

void YoBattle::OnInit()
{
	load_texture("spirikat");
	//...

	sprites = new SpriteSystem();

	//...
	test = new Entity();
	test->push(new Sprite("spirikat", 150, 150, 2, 56, 0));
	test->component<Sprite>()->axis->speed = 200;
	test->component<Sprite>()->axis->x = 1;
	test->component<Sprite>()->axis->y = 1;
	sprites->upload(test->component<Sprite>());

	test2 = new Entity();
	test2->push(new Sprite("spirikat", 150, 150, 2, 56, 0));
	test2->component<Sprite>()->axis->speed = 200;
	test2->component<Sprite>()->axis->x = 0;
	test2->component<Sprite>()->axis->y = 1;
	sprites->upload(test2->component<Sprite>());
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
