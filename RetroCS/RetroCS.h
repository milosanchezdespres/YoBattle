#pragma once

#include "Tools/Tools.h"
#include "ECS/ECS.h"
#include "Window/Window.h"

inline GameData* game() { return GameWindow::instance().data; }

//...

using namespace RetroCS;
