#include "MainWindow.h"

#include <iostream>
#include <chrono>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using namespace std;


std::unique_ptr<MainWindow> MainWindow::_selfInstance;


MainWindow::MainWindow(const std::string &title, glm::uvec2 windowSize):
    _window(nullptr),
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

    _window = glfwCreateWindow(_windowSize.x, _windowSize.y, title.c_str(), NULL, NULL);
    if (!_window)
    {
        cout<<"Window not created!!!!\n";
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(_window);
//    glfwSwapInterval(1);

    if(glewInit() != GLEW_OK)
    {
        cout<<"GLEW initialization error!!!!"<<endl;
        exit(-1);
    }
    cout<<"Dirver Version: "<<glGetString(GL_VERSION)<<endl;

    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGui::StyleColorsDark();

    _scene.GetCamera().ResizeViewport(_windowSize.x, _windowSize.y);

    glClearColor(0.2, 0.2, 0.2, 1);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_POINT_SIZE);

    RegisterCallbacks();
}

void MainWindow::RegisterCallbacks()
{
    glfwSetWindowSizeCallback(_window, [](GLFWwindow*, int width, int height)
    {
        MainWindow::Get()->_scene.OnWindowResize(width, height);
    });

    glfwSetFramebufferSizeCallback(_window, [](GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
        MainWindow::Get()->_scene.OnViewportResize(width, height);
    });

    glfwSetKeyCallback(_window, [](GLFWwindow*, int key, int scancode, int action, int mods){
        InputHandler::Get()->OnKey(key, scancode, action, mods);
    });

    glfwSetMouseButtonCallback(_window, [](GLFWwindow*, int button, int action, int mods){
        InputHandler::Get()->OnMouseButton(button, action, mods);
    });

    glfwSetScrollCallback(_window, [](GLFWwindow*, double xoffset, double yoffset){
        InputHandler::Get()->OnScroll(xoffset, yoffset);
    });

    glfwSetCursorPosCallback(_window, [](GLFWwindow*, double xpos, double ypos){
        InputHandler::Get()->OnMouseMove(xpos, ypos);
    });
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

Scene *MainWindow::GetScene()
{
    return &_scene;
}

void MainWindow::Run()
{
    double upsTime = 1./60.;

    double frameTime = 0;
    double updateTimer = 0.;
    while (!glfwWindowShouldClose(_window))
    {
        double frameStart = glfwGetTime();

        HandleEvents();

        if(updateTimer >= upsTime)
        {
            _scene.Update(updateTimer);
            updateTimer = 0;
        }

        Clear();
        if(_useImgui)
            ClearImGui();

        _scene.Render();

        if(_useImgui)
            RenderImGui();

        SwapBuffers();

        frameTime = glfwGetTime() - frameStart;
        updateTimer += frameTime;
    }
}

void MainWindow::UseImGui(bool use)
{
    _useImgui = use;
}

bool MainWindow::IsCreated()
{
    return _selfInstance != nullptr;
}

void MainWindow::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
