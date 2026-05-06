#include "libraries/m_Function.h"
#include "services/m_RunService.h"
#include "services/m_TaskScheduler.h"

namespace Mariner {

    namespace Services {

        m_RunService* m_RunService::New() {

            static m_RunService* Instance = nullptr;

                if(Instance == nullptr) {

                    Instance = new m_RunService();
                    Instance->Name = "Run Service";
                    Instance->ClassName = "m_RunService";
                    Instance->m_Initialize();

                }

            return Instance;

        }

        void m_RunService::m_Initialize() {

            this->PhysicsJob->Name = "m_RunService::PhysicsJob";
            this->PhysicsJob->Cyclic = true;
            this->PhysicsJob->Function = Mariner::Libraries::m_Function([this](){

                this->PreSimulation.Fire();
                this->PostSimulation.Fire();

            });

            this->RenderJob->Name = "m_RunService::RenderJob";
            this->RenderJob->Cyclic = true;
            this->RenderJob->OnMainThread = true;
            this->RenderJob->Function = Mariner::Libraries::m_Function([this](){

                this->PreRender.Fire();
                this->RenderStepped.Fire();

            });

            this->HeartbeatJob->Name = "m_RunService::Heartbeat";
            this->HeartbeatJob->Cyclic = true;
            this->HeartbeatJob->Function = Mariner::Libraries::m_Function([this](){

                this->Heartbeat.Fire();

            });

            auto TaskScheduler = Mariner::Services::m_TaskScheduler::New();
            TaskScheduler->AddTask(this->RenderJob);

        }

        void m_RunService::Run() {

            auto TaskScheduler = Mariner::Services::m_TaskScheduler::New();
            this->RunState = Mariner::Enums::m_RunState::RUNNING;

            TaskScheduler->AddTask(this->PhysicsJob);
            TaskScheduler->AddTask(this->HeartbeatJob);

        }

        void m_RunService::Pause() {

            auto TaskScheduler = Mariner::Services::m_TaskScheduler::New();
            this->RunState = Mariner::Enums::m_RunState::PAUSED;

            TaskScheduler->RemoveTask(this->PhysicsJob);
            TaskScheduler->RemoveTask(this->HeartbeatJob);

        }

        void m_RunService::Stop() {

            auto TaskScheduler = Mariner::Services::m_TaskScheduler::New();
            this->RunState = Mariner::Enums::m_RunState::STOPPED;

            TaskScheduler->RemoveTask(this->PhysicsJob);
            TaskScheduler->RemoveTask(this->HeartbeatJob);

        }

    }

}