#pragma once
#include "Core.h"
#include "../Events/KeyEvent.h"
#include "../Debug/Logger.h"

namespace Dizzy
{
    class DIZZY_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    // To be defined in Client
    Application* CreateApplication();
}
