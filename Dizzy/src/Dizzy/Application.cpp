#include "Application.h"
#include "Logger.h"
#include "Events/KeyEvent.h"


namespace Dizzy
{
	Application::Application() = default;

	Application::~Application() = default;

	void Application::Run()
	{
		while (true)
		{
			KeyPressedEvent e(111, 2);
			if (e.IsInCategory(EventCategoryInput))
			{
				DIZZY_TRACE(format_event(e));
			}
		}
	}
}
