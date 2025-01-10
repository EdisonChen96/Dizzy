#pragma once
#include "Core.h"
#include "Dizzy/Core/LayerStack.h"
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

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
    private:
        bool OnWindowClose(WindowCloseEvent& e);
        std::unique_ptr<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;
    };

    // To be defined in Client
    Application* CreateApplication();
}
