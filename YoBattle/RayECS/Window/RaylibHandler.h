#pragma once

#include "Utils.h"

class RaylibHandler : public SceneManager
{
	public:
		Color background;

		RaylibHandler(string title);
		~RaylibHandler();

		void load_texture(string _alias);
		void unload_texture(string _alias);
		bool is_texture_loaded(string _alias);
		Texture2D& texture(string alias);

		void blit(Sprite* sprite);
		void write(string text, int font_size, float x, float y, Color color = BLACK);

		void Update();

		int screen_width();
		int screen_height();

	protected:
		Vector2* __position;
		Rectangle* __sourceRec;

		vector<Texture2D> textures;
		unordered_map<string, int> textureByAlias;

		virtual void OnInit() {};
		virtual void OnEvent() {};
		virtual void OnUpdate(float delta) {};
		virtual void OnDraw() {};
};
