#include "objects/m_Window.h"
#include "libraries/m_Function.h"

#include "services/m_RunService.h"
#include "services/m_TaskScheduler.h"
#include "services/m_StorageService.h"

namespace Mariner {

    namespace Objects {

        m_Window* m_Window::New() {

            m_Window* Instance = new m_Window();
            Instance->Name = "Window";
            Instance->ClassName = "m_Window";
            return Instance;

        }

        void m_Window::CreateWindow() {

            auto RunService = Services::m_RunService::New();
            auto TaskScheduler = Services::m_TaskScheduler::New();
            auto StorageService = Services::m_StorageService::New();

            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

            this->WindowHandle = glfwCreateWindow(this->Width, this->Height, this->Name.ToCString(), NULL, NULL);

            StorageService->StoreInternal("m_EngineWindowHandle", this);
            StorageService->StoreInternal("m_NativeWindowHandle", this->WindowHandle);

            RunService->PreRender.Connect(Mariner::Libraries::m_Function([this, RunService, TaskScheduler](){

                if(glfwWindowShouldClose(this->WindowHandle)) {

                    glfwDestroyWindow(this->WindowHandle);
                    glfwTerminate();

                    RunService->Stop();
                    TaskScheduler->Halt();

                }

                glfwPollEvents();

            }));

        }

    }

}