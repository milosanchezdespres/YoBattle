#pragma once

#include "raylib.h"

namespace RAYWIN
{
    struct BTN
    {
        KeyboardKey key;
        GamepadButton gamepad;
        bool gamepad_enabled;

        BTN() {}

        void init(KeyboardKey _key, GamepadButton _gamepad = GAMEPAD_BUTTON_UNKNOWN)
        {
            key = _key;
            gamepad = _gamepad;
            gamepad_enabled = _gamepad != GAMEPAD_BUTTON_UNKNOWN;
        }

        bool is_down() { return IsKeyDown(key) || (gamepad_enabled && IsGamepadAvailable(0) && IsGamepadButtonDown(0, gamepad)); }
    };
}