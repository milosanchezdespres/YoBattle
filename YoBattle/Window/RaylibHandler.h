#pragma once

#include "raylib.h"

#include <string>
using namespace std;

class RaylibHandler
{
	public:
		RaylibHandler(string title);
		~RaylibHandler();

		void Update();

	protected:
		virtual void OnInit() {};
		virtual void OnUpdate(float delta) {};
		virtual void OnDraw() {};
};