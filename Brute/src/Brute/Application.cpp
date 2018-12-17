#include "Application.h"

#include "Brute/Events/ApplicationEvent.h"
#include "Brute/Log.h"

namespace Brute {

	Application::Application()
	{
	}


	Application::~Application()
	{
	}

	void Application::Run()
	{

		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			BT_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			BT_TRACE(e);
		}

		while (true);
	}

}
