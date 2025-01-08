#pragma once
#include "Core.h"
#include "Events/Event.h"

namespace Dizzy
{
    class __declspec(dllexport) Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // To be defined in Client
    Application* CreateApplication();
}
