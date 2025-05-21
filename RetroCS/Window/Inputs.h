#pragma once

#include "raylib.h"

namespace RetroCS
{
    namespace GameWindow
    {
        struct BTN
        {
            KeyboardKey key;
            GamepadButton gamepad;

            BTN() {}

            void init(KeyboardKey _key, GamepadButton _gamepad = GAMEPAD_BUTTON_UNKNOWN)
            {
                key = _key;
                gamepad = _gamepad;
            }

            bool is_down()
            {
                if (gamepad != GAMEPAD_BUTTON_UNKNOWN && IsGamepadAvailable(0))
                {
                    if (IsGamepadButtonDown(0, gamepad))
                        return true;
                }

                return IsKeyDown(key);
            }
        };
    }
}