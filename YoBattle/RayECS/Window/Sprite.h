#pragma once

#include "../ECS/ECS_includes.h"

struct Sprite : public Component
{
	float x, y, rotation;
	int size, scale, h_tile_index, v_tile_index;
	string texture;
	bool visible;

	Sprite() : Component()
	{
		x = 0;
		y = 0;

		rotation = 0;

		h_tile_index = 0;
		v_tile_index = 0;
		size = 0;
		scale = 1;

		texture = "";

		visible = true;
	}
};