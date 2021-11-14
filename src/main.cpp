#include <iostream>

#include "MainWindow.h"

using namespace std;



int main()
{
    auto* window = MainWindow::Create("FV Game", {1280, 720});
    window->UseImGui(true);
    window->Run();

    return 0;
}
