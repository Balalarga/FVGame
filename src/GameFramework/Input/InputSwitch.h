#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <vector>
#include <functional>


enum class InputState
{
    Released, Pressed, Repeated
};

enum class InputMode: uint8_t
{
    Ctrl, Shift, Alt, EndMode
};


class InputSwitch
{
    friend class InputHandler;
public:
    InputSwitch() = default;
    virtual ~InputSwitch() = default;

    const bool& IsMode(const InputMode& mode) const;
    const InputState& State() const;

    void AddOnPress(const std::function<void()>& func) const;
    void AddOnRelease(const std::function<void()>& func) const;


private:
    void SetState(const InputState& state);
    void SetMode(const InputMode& mode, bool state);

    bool _modes[static_cast<uint8_t>(InputMode::EndMode)];
    InputState _state;

    mutable std::vector<std::function<void()>> _onPress;
    mutable std::vector<std::function<void()>> _onRelease;
};


inline const bool &InputSwitch::IsMode(const InputMode &mode) const
{
    return _modes[static_cast<uint8_t>(mode)];
}

inline const InputState &InputSwitch::State() const
{
    return _state;
}


#endif // INPUTDATA_H
