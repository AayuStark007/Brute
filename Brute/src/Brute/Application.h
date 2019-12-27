#pragma once

#include "Core.h"

#include "Window.h"
#include "Brute/LayerStack.h"
#include "Brute/Events/Event.h"
#include "Brute/Events/ApplicationEvent.h"

#include "Brute/ImGui/ImGuiLayer.h"

#include "Brute/Renderer/Shader.h"
#include "Brute/Renderer/Buffer.h"


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

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray;

		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	private:
		static Application* s_Instance;
	};

	// To be defined in Client
	Application* CreateApplication();

}


