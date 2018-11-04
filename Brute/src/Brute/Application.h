#pragma once

#include "Core.h"

namespace Brute {

	class BRUTE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in Client
	Application* CreateApplication();

}


