#include "InputHandler.h"


bool &KeyData::ModeAt(KeyMode name)
{
    return modes[static_cast<uint8_t>(name)];
}


std::unique_ptr<InputHandler> InputHandler::_selfInstance;

InputHandler *InputHandler::Get()
{
    if(!_selfInstance.get())
        _selfInstance.reset(new InputHandler);
    return _selfInstance.get();
}

KeyData InputHandler::Key(int key)
{
    return _keys[key];
}

void InputHandler::OnKey(int key, int scancode, int action, int mods)
{
    if(key == -1)
        return;

    KeyData& keyData = _keys[key];

    switch(action)
    {
    case GLFW_PRESS:
        keyData.state = KeyState::Pressed;
        break;
    case GLFW_REPEAT:
        keyData.state = KeyState::Repeated;
        break;
    default:
        keyData.state = KeyState::Released;
        break;
    }

    keyData.ModeAt(KeyMode::Ctrl) = mods & GLFW_MOD_CONTROL;
    keyData.ModeAt(KeyMode::Shift) = mods & GLFW_MOD_SHIFT;
    keyData.ModeAt(KeyMode::Alt) = mods & GLFW_MOD_ALT;
}

void InputHandler::OnMouseButton(int button, int action, int mods)
{

}

void InputHandler::OnScroll(float xoffset, float yoffset)
{

}

void InputHandler::OnMouseMove(float xpos, float ypos)
{

}

