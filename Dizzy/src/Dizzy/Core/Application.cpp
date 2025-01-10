#include "dzpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace Dizzy
{
#define BIND_EVENT_FUNC(x) [this](Event& e) { x(e); }      // Lambda for event binding

    Application::Application()
    {
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FUNC(Application::OnEvent));
    };

    Application::~Application() = default;

    void Application::OnEvent(Event& e)
    {
        DIZZY_CORE_INFO("{0}", format_event(e));
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }
}
