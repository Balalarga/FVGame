#include "InputHandler.h"
#include <iostream>

std::unique_ptr<InputHandler> InputHandler::_selfInstance;

InputHandler *InputHandler::Get()
{
    if(!_selfInstance.get())
        _selfInstance.reset(new InputHandler);
    return _selfInstance.get();
}

void InputHandler::OnKey(int key, int scancode, int action, int mods)
{
    if(key == -1)
        return;

    InputSwitch& keyData = _keys[key];

    switch(action)
    {
    case GLFW_PRESS:
        keyData.SetState(InputState::Pressed);
        break;
    case GLFW_REPEAT:
        keyData.SetState(InputState::Repeated);
        break;
    default:
        keyData.SetState(InputState::Released);
        break;
    }
    keyData.SetMode(InputMode::Shift, mods & GLFW_MOD_SHIFT);
    keyData.SetMode(InputMode::Ctrl, mods & GLFW_MOD_CONTROL);
    keyData.SetMode(InputMode::Alt, mods & GLFW_MOD_ALT);
}

void InputHandler::OnMouseButton(int button, int action, int mods)
{
    if(button == -1)
        return;

    InputSwitch& keyData = _mouseButtons[button];
    switch(action)
    {
    case GLFW_PRESS:
        keyData.SetState(InputState::Pressed);
        break;
    case GLFW_REPEAT:
        keyData.SetState(InputState::Repeated);
        break;
    default:
        keyData.SetState(InputState::Released);
        break;
    }
    keyData.SetMode(InputMode::Shift, mods & GLFW_MOD_SHIFT);
    keyData.SetMode(InputMode::Ctrl, mods & GLFW_MOD_CONTROL);
    keyData.SetMode(InputMode::Alt, mods & GLFW_MOD_ALT);
}

void InputHandler::OnScroll(float xoffset, float yoffset)
{

}

void InputHandler::OnMouseMove(float xpos, float ypos)
{

}

