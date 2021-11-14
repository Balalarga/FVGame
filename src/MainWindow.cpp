#include "MainWindow.h"

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "OpenglErrorHandle.h"

using namespace std;

std::unique_ptr<MainWindow> MainWindow::_selfInstance;

MainWindow::MainWindow(const std::string &title, glm::uvec2 windowSize):
    _windowTitle(title),
    _windowSize(windowSize),
    _useImgui(false)
{
    if (!glfwInit())
    {
        cout<<"GLFW initialization error!!!!"<<endl;
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    _window = glfwCreateWindow(_windowSize.x, _windowSize.y, "Hello World", NULL, NULL);
    if (!_window)
    {
        cout<<"Window not created!!!!\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(_window);
    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK)
    {
        cout<<"GLEW initialization error!!!!"<<endl;
        exit(-1);
    }
    cout<<"OpenGL Version: "<<glGetString(GL_VERSION)<<endl;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 460 core");
    ImGui::StyleColorsDark();
}

MainWindow::~MainWindow()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
}

MainWindow *MainWindow::Create(const std::string &title, glm::uvec2 windowSize)
{
    if(!_selfInstance.get())
        _selfInstance.reset(new MainWindow(title, windowSize));
    return _selfInstance.get();
}

MainWindow *MainWindow::Get()
{
    return _selfInstance.get();
}

void MainWindow::Run()
{
    while (!glfwWindowShouldClose(_window))
    {
        Clear();
        if(_useImgui)
            ClearImGui();

        Render();
        if(_useImgui)
            RenderImGui();

        SwapBuffers();

        HandleEvents();
    }
}

void MainWindow::UseImGui(bool use)
{
    _useImgui = use;
}

void MainWindow::Clear()
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void MainWindow::Render()
{

}

void MainWindow::Update(float dt)
{

}

void MainWindow::HandleEvents()
{
    glfwPollEvents();
}

void MainWindow::ClearImGui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void MainWindow::RenderImGui()
{
    ImGui::Begin("Menu");
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MainWindow::SwapBuffers()
{
    glfwSwapBuffers(_window);
}
