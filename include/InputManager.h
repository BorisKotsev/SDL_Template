#pragma once

#include "Engine.h"
#include <SDL.h>

class InputManager {
public:
    InputManager();
    ~InputManager();

    static int2 m_mouseCoor;
    static int2 m_joystickCoor;
    static const Uint8* m_keyboardState;

    void handleInput();
    void setMouseMultiply(float2 multyplier);
    void setJoystickMultiply(float2 multiplier);

    static bool isMousePressed();

private:
    SDL_Event m_event;
    SDL_Joystick* m_joystick;
    float2 m_mouseMultiply;
    float2 m_joystickMultiply;

    static bool m_mouseIsPressed;

    void handleJoystickAxisMotion(const SDL_JoyAxisEvent& event);
    void handleJoystickButtonDown(const SDL_JoyButtonEvent& event);
    void handleJoystickButtonUp(const SDL_JoyButtonEvent& event);
};

bool isAnyKeyPressed();
bool isKeyPressed(SDL_Scancode code);
