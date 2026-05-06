#pragma once

#include "objects/m_Task.h"
#include "enums/m_RunState.h"
#include "services/m_Service.h"
#include "libraries/m_Signal.h"

namespace Mariner {

    namespace Services {

        struct m_RunService : public m_Service {

            public:

                static m_RunService* New();

                Mariner::Enums::m_RunState RunState =  Mariner::Enums::m_RunState::STOPPED;

                void Run();
                void Pause();
                void Stop();

                Mariner::Libraries::m_Signal PreRender;
                Mariner::Libraries::m_Signal RenderStepped;
                Mariner::Libraries::m_Signal PreSimulation;
                Mariner::Libraries::m_Signal PostSimulation;
                Mariner::Libraries::m_Signal Heartbeat;

            protected:

                m_RunService() = default;
                virtual ~m_RunService() = default;

            private:

                virtual void m_Initialize() override;

                Mariner::Objects::m_Task* RenderJob = Mariner::Objects::m_Task::New();
                Mariner::Objects::m_Task* PhysicsJob = Mariner::Objects::m_Task::New();
                Mariner::Objects::m_Task* HeartbeatJob = Mariner::Objects::m_Task::New();

        };

    }

}