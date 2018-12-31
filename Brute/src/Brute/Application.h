#pragma once

#include "Core.h"

#include "Window.h"
#include "Brute/LayerStack.h"
#include "Brute/Events/Event.h"
#include "Brute/Events/ApplicationEvent.h"


namespace Brute {

	class BRUTE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	// To be defined in Client
	Application* CreateApplication();

}


