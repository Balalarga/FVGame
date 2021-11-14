#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class MainWindow
{
public:
    ~MainWindow();
    static MainWindow* Create(const std::string& title, glm::uvec2 windowSize = {800, 600});
    static MainWindow* Get();

    void Run();
    void UseImGui(bool use);


protected:
    virtual void Clear();
    virtual void Render();
    virtual void Update(float dt);
    virtual void HandleEvents();
    virtual void ClearImGui();
    virtual void RenderImGui();
    void SwapBuffers();


private:
    MainWindow(const std::string& title, glm::uvec2 windowSize);
    static std::unique_ptr<MainWindow> _selfInstance;

    GLFWwindow* _window = nullptr;
    glm::uvec2 _windowSize;
    std::string _windowTitle;
    bool _useImgui;
};

#endif // MAINWINDOW_H
