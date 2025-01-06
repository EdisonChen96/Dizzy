#include "Application.h"
#include "Logger.h"

namespace Dizzy
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (true)
		{
			DIZZY_CORE_INFO("Tick Running");
		}
	}
}
