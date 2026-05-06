#include <stdio.h>
#include <chrono>
#include "Mariner/Mariner.h"

using namespace Mariner::Enums;
using namespace Mariner::Objects;
using namespace Mariner::Libraries;
using namespace Mariner::Services;

int main() {

    auto Workspace = m_Workspace::New();
    auto RunService = m_RunService::New();
    auto TaskScheduler = m_TaskScheduler::New();

    RunService->SetParent(m_Game);
    TaskScheduler->SetParent(m_Game);

    RunService->PreRender.Connect(m_Function([]() {

        printf("%s\n", "Hello");

    }));

    m_Window* Window = m_Window::New();
    Window->Width  = 800;
    Window->Height = 600;
    Window->SetParent(m_Game);
    Window->CreateWindow();

    auto Camera = m_Camera::New();
    Camera->SetParent(Workspace);
    Camera->StartRendering();

    RunService->Run();
    //TaskScheduler->Start();

    return 0;

}