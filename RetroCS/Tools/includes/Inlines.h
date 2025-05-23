#pragma once

#include "Externals.h"

inline void debug(string value) { cout << "<< " + value  + " <<" << endl; }

inline void debug(float value) { cout << "<< " + to_string(value)  + " <<" << endl; }

inline void debug(int value) { cout << "<< " + to_string(value)  + " <<" << endl; }

namespace std
{
    std::vector<std::string> split(const std::string& str, char delim)
    {
        std::stringstream ss(str);
        std::string item;
        std::vector<std::string> tokens;
        while (std::getline(ss, item, delim)) { tokens.push_back(item); }
        return tokens;
    }

    // Keyboard keys map
    std::unordered_map<std::string, KeyboardKey> raylib_key_map = 
    {
        {"KEY_APOSTROPHE", KEY_APOSTROPHE},
        {"KEY_COMMA", KEY_COMMA},
        {"KEY_MINUS", KEY_MINUS},
        {"KEY_PERIOD", KEY_PERIOD},
        {"KEY_SLASH", KEY_SLASH},
        {"KEY_ZERO", KEY_ZERO},
        {"KEY_ONE", KEY_ONE},
        {"KEY_TWO", KEY_TWO},
        {"KEY_THREE", KEY_THREE},
        {"KEY_FOUR", KEY_FOUR},
        {"KEY_FIVE", KEY_FIVE},
        {"KEY_SIX", KEY_SIX},
        {"KEY_SEVEN", KEY_SEVEN},
        {"KEY_EIGHT", KEY_EIGHT},
        {"KEY_NINE", KEY_NINE},
        {"KEY_SEMICOLON", KEY_SEMICOLON},
        {"KEY_EQUAL", KEY_EQUAL},
        {"KEY_A", KEY_A},
        {"KEY_B", KEY_B},
        {"KEY_C", KEY_C},
        {"KEY_D", KEY_D},
        {"KEY_E", KEY_E},
        {"KEY_F", KEY_F},
        {"KEY_G", KEY_G},
        {"KEY_H", KEY_H},
        {"KEY_I", KEY_I},
        {"KEY_J", KEY_J},
        {"KEY_K", KEY_K},
        {"KEY_L", KEY_L},
        {"KEY_M", KEY_M},
        {"KEY_N", KEY_N},
        {"KEY_O", KEY_O},
        {"KEY_P", KEY_P},
        {"KEY_Q", KEY_Q},
        {"KEY_R", KEY_R},
        {"KEY_S", KEY_S},
        {"KEY_T", KEY_T},
        {"KEY_U", KEY_U},
        {"KEY_V", KEY_V},
        {"KEY_W", KEY_W},
        {"KEY_X", KEY_X},
        {"KEY_Y", KEY_Y},
        {"KEY_Z", KEY_Z},
        {"KEY_LEFT_BRACKET", KEY_LEFT_BRACKET},
        {"KEY_BACKSLASH", KEY_BACKSLASH},
        {"KEY_RIGHT_BRACKET", KEY_RIGHT_BRACKET},
        {"KEY_GRAVE", KEY_GRAVE},
        {"KEY_SPACE", KEY_SPACE},
        {"KEY_ESCAPE", KEY_ESCAPE},
        {"KEY_ENTER", KEY_ENTER},
        {"KEY_TAB", KEY_TAB},
        {"KEY_BACKSPACE", KEY_BACKSPACE},
        {"KEY_INSERT", KEY_INSERT},
        {"KEY_DELETE", KEY_DELETE},
        {"KEY_RIGHT", KEY_RIGHT},
        {"KEY_LEFT", KEY_LEFT},
        {"KEY_DOWN", KEY_DOWN},
        {"KEY_UP", KEY_UP},
        {"KEY_PAGE_UP", KEY_PAGE_UP},
        {"KEY_PAGE_DOWN", KEY_PAGE_DOWN},
        {"KEY_HOME", KEY_HOME},
        {"KEY_END", KEY_END},
        {"KEY_CAPS_LOCK", KEY_CAPS_LOCK},
        {"KEY_SCROLL_LOCK", KEY_SCROLL_LOCK},
        {"KEY_NUM_LOCK", KEY_NUM_LOCK},
        {"KEY_PRINT_SCREEN", KEY_PRINT_SCREEN},
        {"KEY_PAUSE", KEY_PAUSE},
        {"KEY_F1", KEY_F1},
        {"KEY_F2", KEY_F2},
        {"KEY_F3", KEY_F3},
        {"KEY_F4", KEY_F4},
        {"KEY_F5", KEY_F5},
        {"KEY_F6", KEY_F6},
        {"KEY_F7", KEY_F7},
        {"KEY_F8", KEY_F8},
        {"KEY_F9", KEY_F9},
        {"KEY_F10", KEY_F10},
        {"KEY_F11", KEY_F11},
        {"KEY_F12", KEY_F12},
        {"KEY_LEFT_SHIFT", KEY_LEFT_SHIFT},
        {"KEY_LEFT_CONTROL", KEY_LEFT_CONTROL},
        {"KEY_LEFT_ALT", KEY_LEFT_ALT},
        {"KEY_LEFT_SUPER", KEY_LEFT_SUPER},
        {"KEY_RIGHT_SHIFT", KEY_RIGHT_SHIFT},
        {"KEY_RIGHT_CONTROL", KEY_RIGHT_CONTROL},
        {"KEY_RIGHT_ALT", KEY_RIGHT_ALT},
        {"KEY_RIGHT_SUPER", KEY_RIGHT_SUPER},
        {"KEY_KB_MENU", KEY_KB_MENU},
        {"KEY_KP_0", KEY_KP_0},
        {"KEY_KP_1", KEY_KP_1},
        {"KEY_KP_2", KEY_KP_2},
        {"KEY_KP_3", KEY_KP_3},
        {"KEY_KP_4", KEY_KP_4},
        {"KEY_KP_5", KEY_KP_5},
        {"KEY_KP_6", KEY_KP_6},
        {"KEY_KP_7", KEY_KP_7},
        {"KEY_KP_8", KEY_KP_8},
        {"KEY_KP_9", KEY_KP_9},
        {"KEY_KP_DECIMAL", KEY_KP_DECIMAL},
        {"KEY_KP_DIVIDE", KEY_KP_DIVIDE},
        {"KEY_KP_MULTIPLY", KEY_KP_MULTIPLY},
        {"KEY_KP_SUBTRACT", KEY_KP_SUBTRACT},
        {"KEY_KP_ADD", KEY_KP_ADD},
        {"KEY_KP_ENTER", KEY_KP_ENTER},
        {"KEY_KP_EQUAL", KEY_KP_EQUAL},
        {"KEY_BACK", KEY_BACK},
        {"KEY_MENU", KEY_MENU},
        {"KEY_VOLUME_UP", KEY_VOLUME_UP},
        {"KEY_VOLUME_DOWN", KEY_VOLUME_DOWN}
    };

    std::unordered_map<std::string, GamepadButton> raylib_gamepad_map = 
    {
        {"GAMEPAD_BUTTON_UNKNOWN", GAMEPAD_BUTTON_UNKNOWN},
        {"GAMEPAD_BUTTON_LEFT_FACE_UP", GAMEPAD_BUTTON_LEFT_FACE_UP},
        {"GAMEPAD_BUTTON_LEFT_FACE_RIGHT", GAMEPAD_BUTTON_LEFT_FACE_RIGHT},
        {"GAMEPAD_BUTTON_LEFT_FACE_DOWN", GAMEPAD_BUTTON_LEFT_FACE_DOWN},
        {"GAMEPAD_BUTTON_LEFT_FACE_LEFT", GAMEPAD_BUTTON_LEFT_FACE_LEFT},
        {"GAMEPAD_BUTTON_RIGHT_FACE_UP", GAMEPAD_BUTTON_RIGHT_FACE_UP},
        {"GAMEPAD_BUTTON_RIGHT_FACE_RIGHT", GAMEPAD_BUTTON_RIGHT_FACE_RIGHT},
        {"GAMEPAD_BUTTON_RIGHT_FACE_DOWN", GAMEPAD_BUTTON_RIGHT_FACE_DOWN},
        {"GAMEPAD_BUTTON_RIGHT_FACE_LEFT", GAMEPAD_BUTTON_RIGHT_FACE_LEFT},
        {"GAMEPAD_BUTTON_LEFT_TRIGGER_1", GAMEPAD_BUTTON_LEFT_TRIGGER_1},
        {"GAMEPAD_BUTTON_LEFT_TRIGGER_2", GAMEPAD_BUTTON_LEFT_TRIGGER_2},
        {"GAMEPAD_BUTTON_RIGHT_TRIGGER_1", GAMEPAD_BUTTON_RIGHT_TRIGGER_1},
        {"GAMEPAD_BUTTON_RIGHT_TRIGGER_2", GAMEPAD_BUTTON_RIGHT_TRIGGER_2},
        {"GAMEPAD_BUTTON_MIDDLE_LEFT", GAMEPAD_BUTTON_MIDDLE_LEFT},
        {"GAMEPAD_BUTTON_MIDDLE", GAMEPAD_BUTTON_MIDDLE},
        {"GAMEPAD_BUTTON_MIDDLE_RIGHT", GAMEPAD_BUTTON_MIDDLE_RIGHT},
        {"GAMEPAD_BUTTON_LEFT_THUMB", GAMEPAD_BUTTON_LEFT_THUMB},
        {"GAMEPAD_BUTTON_RIGHT_THUMB", GAMEPAD_BUTTON_RIGHT_THUMB}
    };

    std::unordered_map<std::string, GamepadAxis> raylib_gamepad_axis_map =
    {
        {"GAMEPAD_AXIS_LEFT_X", GAMEPAD_AXIS_LEFT_X},
        {"GAMEPAD_AXIS_LEFT_Y", GAMEPAD_AXIS_LEFT_Y},
        {"GAMEPAD_AXIS_RIGHT_X", GAMEPAD_AXIS_RIGHT_X},
        {"GAMEPAD_AXIS_RIGHT_Y", GAMEPAD_AXIS_RIGHT_Y},
        {"GAMEPAD_AXIS_LEFT_TRIGGER", GAMEPAD_AXIS_LEFT_TRIGGER},
        {"GAMEPAD_AXIS_RIGHT_TRIGGER", GAMEPAD_AXIS_RIGHT_TRIGGER}
    };

    std::unordered_map<KeyboardKey, std::string> raylib_key_to_string;
    std::unordered_map<GamepadButton, std::string> raylib_gamepad_button_to_string;
    std::unordered_map<GamepadAxis, std::string> raylib_gamepad_axis_to_string;

    void init_reverse_keys()
    {
        for (auto& pair : raylib_key_map)
            raylib_key_to_string[pair.second] = pair.first;

        for (auto& pair : raylib_gamepad_map)
            raylib_gamepad_button_to_string[pair.second] = pair.first;

        for (auto& pair : raylib_gamepad_axis_map)
            raylib_gamepad_axis_to_string[pair.second] = pair.first;
    }

    std::string to_string(KeyboardKey key, GamepadButton button) { return raylib_key_to_string[key] + ";" + raylib_gamepad_button_to_string[button]; }
}
