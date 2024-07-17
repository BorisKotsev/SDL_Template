#include "InputManager.h"

bool InputManager::m_mouseIsPressed = bool();
int2 InputManager::m_mouseCoor = int2();
int2 InputManager::m_joystickCoor = int2();
const Uint8* InputManager::m_keyboardState = nullptr;

InputManager::InputManager() 
{
    if (SDL_NumJoysticks() > 0) 
    {
        m_joystick = SDL_JoystickOpen(0);
        if (m_joystick == nullptr) 
        {
            // Handle error
        }
    }
    else {
        m_joystick = nullptr;
    }

    // Initialize joystick coordinates and multiplier
    m_joystickCoor = { 0, 0 };
    m_joystickMultiply = { 1.0f, 1.0f };
}

InputManager::~InputManager() 
{
    if (m_joystick) 
    {
        SDL_JoystickClose(m_joystick);
    }
}

void InputManager::setMouseMultiply(float2 multyplier) 
{
    m_mouseMultiply.x = multyplier.x;
    m_mouseMultiply.y = multyplier.y;
}

void InputManager::setJoystickMultiply(float2 multiplier) 
{
    m_joystickMultiply.x = multiplier.x;
    m_joystickMultiply.y = multiplier.y;
}

void InputManager::handleInput() 
{
    m_mouseIsPressed = false;

    while (SDL_PollEvent(&m_event)) 
    {
        switch (m_event.type) 
        {
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&(m_mouseCoor.x), &(m_mouseCoor.y));
            m_mouseCoor.x *= m_mouseMultiply.x;
            m_mouseCoor.y *= m_mouseMultiply.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (m_event.button.button == SDL_BUTTON_LEFT)
            {
                m_mouseIsPressed = true;
            }
            break;
        case SDL_JOYAXISMOTION:
            handleJoystickAxisMotion(m_event.jaxis);
            break;
        case SDL_JOYBUTTONDOWN:
            handleJoystickButtonDown(m_event.jbutton);
            break;
        case SDL_JOYBUTTONUP:
            handleJoystickButtonUp(m_event.jbutton);
            break;
        }
    }
    m_keyboardState = SDL_GetKeyboardState(NULL);
}

void InputManager::handleJoystickAxisMotion(const SDL_JoyAxisEvent& event) 
{
    // Axis motion ranges from -32768 to 32767
    // Normalize to -1.0 to 1.0 and apply multiplier

    const float MAX_JOYSTICK_VALUE = 32767.0f;

    if (event.axis == 0) // X-axis motion
    { 
        float normalizedValue = event.value / MAX_JOYSTICK_VALUE;
        m_joystickCoor.x = static_cast<int>(normalizedValue * m_joystickMultiply.x);
    }
    else if (event.axis == 1) // Y-axis motion
    { 
        float normalizedValue = event.value / MAX_JOYSTICK_VALUE;
        m_joystickCoor.y = static_cast<int>(normalizedValue * m_joystickMultiply.y);
    }
}

void InputManager::handleJoystickButtonDown(const SDL_JoyButtonEvent& event) 
{
    if (event.button == 0) 
    {
        // Button 0 pressed
    }
}

void InputManager::handleJoystickButtonUp(const SDL_JoyButtonEvent& event) 
{
    if (event.button == 0) 
    {
        // Button 0 released
    }
}

bool InputManager::isMousePressed() 
{
    return m_mouseIsPressed;
}

bool isAnyKeyPressed() 
{
    int numOfKeys = 322;

    for (int i = 0; i < numOfKeys; i ++) 
    {
        if (InputManager::m_keyboardState[i]) 
        {
            return true;
        }
    }
    return false;
}

bool isKeyPressed(SDL_Scancode code) 
{
    return InputManager::m_keyboardState[code];
}
