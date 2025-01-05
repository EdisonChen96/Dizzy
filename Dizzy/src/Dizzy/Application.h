#pragma once
#include "Core.h"
#include "Application.h"

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
