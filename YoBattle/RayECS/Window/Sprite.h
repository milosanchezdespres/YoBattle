#pragma once

#include "../ECS/ECS_includes.h"

struct Sprite : public Component
{
	float x, y;
	int size, tile_index;
	string texture;
	bool visible;

	Sprite() : Component()
	{
		x = 0;
		y = 0;

		tile_index = 0;
		size = 8;

		texture = "";

		visible = true;
	}
};