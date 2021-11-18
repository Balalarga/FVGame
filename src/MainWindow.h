#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Graphics/Scene.h"

class MainWindow
{
public:
    ~MainWindow();
    static MainWindow* Create(const std::string& title, glm::uvec2 windowSize = {800, 600});
    static MainWindow* Get();

    Scene* GetScene();

    void Run();
    void UseImGui(bool use);


protected:
    virtual void Clear();
    virtual void Update(float dt);
    virtual void HandleEvents();
    virtual void ClearImGui();
    virtual void RenderImGui();
    void SwapBuffers();

    // Events
    virtual void OnResize(int width, int height);
    virtual void OnKey(int key, int scancode, int action, int mods);
    virtual void OnMouseButton(int button, int action, int mods);
    virtual void OnScroll(double xoffset, double yoffset);
    virtual void OnMouseMove(double xpos, double ypos);


private:
    MainWindow(const std::string& title, glm::uvec2 windowSize);
    static std::unique_ptr<MainWindow> _selfInstance;

    void RegisterCallbacks();

    GLFWwindow* _window = nullptr;
    glm::uvec2 _windowSize;
    std::string _windowTitle;
    bool _useImgui;

    std::unique_ptr<Scene> _scene;
};

#endif // MAINWINDOW_H
