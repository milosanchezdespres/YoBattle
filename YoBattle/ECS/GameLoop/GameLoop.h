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

		void load_texture(string name, string path = "");
		void unload_texture(string name);
		void unload_all_textures();

		void blit(Sprite* sprite);

	protected:
		const Texture2D& texture(string name);

		virtual void OnInit() {};
		virtual void OnUpdate() {};
		virtual void OnDraw() {};
		virtual void OnClose() {};

	private:
		bool _initialized;
		map<string, Texture2D> _textures;

		Rectangle __source__buffer, __dest__buffer;
};