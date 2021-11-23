#include "InputSwitch.h"


void InputSwitch::AddOnPress(const std::function<void ()> &func) const
{
    _onPress.push_back(func);
}

void InputSwitch::AddOnRelease(const std::function<void ()> &func) const
{
    _onRelease.push_back(func);
}

void InputSwitch::SetState(const InputState &state)
{
    _state = state;

    auto execCalls = [](std::vector<std::function<void()>> funcs){
        for(auto& f: funcs)
            f();
    };

    switch (_state)
    {
    case InputState::Pressed:
        execCalls(_onPress);
        break;
    case InputState::Released:
        execCalls(_onRelease);
        break;
    default:
        break;
    }
}

void InputSwitch::SetMode(const InputMode &mode, bool state)
{
    _modes[static_cast<uint8_t>(mode)] = state;
}
