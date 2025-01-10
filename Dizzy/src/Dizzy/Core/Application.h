#pragma once
#include "Core.h"
#include "Dizzy/Window.h"
#include "Dizzy/Events/ApplicationEvent.h"

namespace Dizzy
{
    class DIZZY_API Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();

        void OnEvent(Event& e);

    private:
        bool OnWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
    };

    // To be defined in Client
    Application* CreateApplication();
}
