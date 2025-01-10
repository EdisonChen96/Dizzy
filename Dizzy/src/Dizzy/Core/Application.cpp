#include "dzpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace Dizzy
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	};

	Application::~Application() = default;

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
