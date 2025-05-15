#include "YoBattle.h"

YoBattle::YoBattle() : GameLoop("YoBattle") {}

void YoBattle::OnInit()
{
	load_texture("spirikat");
	//...

	scene = new Scene();
	scene->add(new SpriteSystem());
	scene->add(new DebugSystem());

	scene->push("test", new Entity());
	scene->push("test2", new Entity());
	scene->push("test3", new Entity());

	scene->entity("test")->push(new Sprite("spirikat", 150, 150, 3, 56, 0));
	scene->entity("test")->push(new Axis(200));
	scene->entity("test")->component<Axis>()->x = 1;
	scene->entity("test")->component<Axis>()->y = 1;
	scene->entity("test")->push(new Debug("hello world"));
	scene->sys<SpriteSystem>()->upload(scene->entity("test"));
	scene->sys<DebugSystem>()->upload(scene->entity("test"));

	scene->entity("test2")->push(new Sprite("spirikat", 150, 150, 3, 56, 0));
	scene->entity("test2")->push(new Axis(200));
	scene->entity("test2")->component<Axis>()->x = 0;
	scene->entity("test2")->component<Axis>()->y = 1;
	scene->sys<SpriteSystem>()->upload(scene->entity("test2"));

	scene->entity("test3")->push(new Sprite("spirikat", 150, 150, 3, 56, 0));
	scene->entity("test3")->push(new Axis(200));
	scene->entity("test3")->component<Axis>()->x = 1;
	scene->entity("test3")->component<Axis>()->y = 0;
	scene->sys<SpriteSystem>()->upload(scene->entity("test3"));
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
