#pragma once

#include "Utils.h"

class RaylibHandler
{
	public:
		RaylibHandler(string title);
		~RaylibHandler();

		void load_texture(string _alias);
		void unload_texture(string _alias);
		bool is_texture_loaded(string _alias);
		Texture2D& texture(string alias);

		void blit(Sprite* sprite);

		void Update();

	protected:
		vector<Texture2D> textures;
		unordered_map<string, int> textureByAlias;

		virtual void OnInit() {};
		virtual void OnUpdate(float delta) {};
		virtual void OnDraw() {};

	private:
		Vector2 __position;
		Rectangle __sourceRec;
};
