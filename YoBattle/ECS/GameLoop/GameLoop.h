#pragma once

#include "raylib.h"

#include "../ECS.h"
using namespace ECS;

#include <map>
#include <string>
using namespace std;

class GameLoop
{
	public:
		GameLoop(string title);
		~GameLoop();

		void Update();

	protected:
		void load_texture(string name, string path = "");
		void unload_texture(string name);
		const Texture2D& texture(string name);

		void blit(Sprite* sprite);

		virtual void OnInit() {};
		virtual void OnEvent() {};
		virtual void OnUpdate() {};
		virtual void OnDraw() {};
		virtual void OnClose() {};

	private:
		bool _initialized;
		map<string, Texture2D> _textures;

		Rectangle __source__buffer, __dest__buffer;
};