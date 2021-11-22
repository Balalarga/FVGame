#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <memory>
#include <GLFW/glfw3.h>

enum class KeyState
{
    Released, Pressed, Repeated
};

enum class KeyMode: uint8_t
{
    Ctrl, Shift, Alt, LastMode
};


struct KeyData
{
    KeyState state = KeyState::Released;
    bool modes[static_cast<uint8_t>(KeyMode::LastMode)];

    bool& ModeAt(KeyMode name);
};


class InputHandler
{
    friend class MainWindow;
public:
    static InputHandler* Get();

    KeyData Key(int key);


private:
    InputHandler() = default;
    static std::unique_ptr<InputHandler> _selfInstance;

    void OnKey(int key, int scancode, int action, int mods);
    void OnMouseButton(int button, int action, int mods);
    void OnScroll(float xoffset, float yoffset);
    void OnMouseMove(float xpos, float ypos);


    std::array<KeyData, GLFW_KEY_LAST+1> _keys;
};

#endif // INPUTHANDLER_H
