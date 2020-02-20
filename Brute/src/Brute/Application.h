#pragma once

#include "Core.h"

#include "Window.h"

#include "Brute/LayerStack.h"
#include "Brute/Events/Event.h"
#include "Brute/Events/ApplicationEvent.h"

#include "Brute/Core/TimeStep.h"

#include "Brute/ImGui/ImGuiLayer.h"

namespace Brute {

	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();

}


