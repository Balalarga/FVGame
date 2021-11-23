#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <memory>
#include <vector>
#include <functional>
#include <GLFW/glfw3.h>

#include "InputSwitch.h"


class InputHandler
{
    friend class MainWindow;
public:
    static InputHandler* Get();

    inline const InputSwitch& Key(int key) { return _keys[key]; }
    inline const InputSwitch& MouseButton(int button) { return _mouseButtons[button]; }


private:
    InputHandler() = default;
    static std::unique_ptr<InputHandler> _selfInstance;

    void OnKey(int key, int scancode, int action, int mods);
    void OnMouseButton(int button, int action, int mods);
    void OnScroll(float xoffset, float yoffset);
    void OnMouseMove(float xpos, float ypos);

    std::array<InputSwitch, GLFW_KEY_LAST+1> _keys;
    std::array<InputSwitch, GLFW_MOUSE_BUTTON_8+1> _mouseButtons;
};

#endif // INPUTHANDLER_H
