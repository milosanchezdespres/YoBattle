#include "YoBattle.h"
#include "MasterInclude.h"

YoBattle::YoBattle() : GameLoop("YoBattle") {}

void YoBattle::OnInit()
{
	scene = new Scene(this, "test", { "spirikat" });
	scene->add(new ControllerSystem());
	//scene->load();

	scene->push("test", new Character(scene, "spirikat", 56, 3, 300));
	scene->entity<Character>("test")->push(new Controller());
	scene->sys<ControllerSystem>()->upload(scene->entity("test"));

	scene->push("test2", new Character(scene, "spirikat", 56, 3, 300));
	scene->entity<Character>("test2")->component<Axis>()->x = 0;
	scene->entity<Character>("test2")->component<Axis>()->y = 1;

	scene->push("test3", new Character(scene, "spirikat", 56, 3, 300));
	scene->entity<Character>("test3")->component<Axis>()->x = 1;
	scene->entity<Character>("test3")->component<Axis>()->y = 0;

	//scene->save();
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
}
