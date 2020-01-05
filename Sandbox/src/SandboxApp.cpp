#include <Brute.h>

#include "imgui/imgui.h"

class ExampleLayer : public Brute::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
		m_VertexArray.reset(Brute::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<Brute::VertexBuffer> triangleVB;
		triangleVB.reset(Brute::VertexBuffer::Create(vertices, sizeof(vertices)));
		Brute::BufferLayout layout = {
			{ Brute::ShaderDataType::Float3, "a_Position" },
			{ Brute::ShaderDataType::Float4, "a_Color" }
		};
		triangleVB->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(triangleVB);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Brute::IndexBuffer> triangleIB;
		triangleIB.reset(Brute::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(triangleIB);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Brute::Shader::Create(vertexSrc, fragmentSrc));
	}

	void OnUpdate() override
	{
		//BT_INFO("ExampleLayer::Update");

		//Brute::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		//Brute::RenderCommand::Clear();

		Brute::Renderer::BeginScene();

		m_Shader->Bind();
		Brute::Renderer::Submit(m_VertexArray);

		Brute::Renderer::EndScene();

		if (Brute::Input::IsKeyPressed(BT_KEY_Y))
			BT_TRACE("Y key is pressed (poll)!");
	}

	void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Brute::Event& event) override
	{
		//BT_TRACE("{0}", event);
		if (event.GetEventType() == Brute::EventType::KeyPressed)
		{
			Brute::KeyPressedEvent& e = (Brute::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BT_KEY_Y)
				BT_TRACE("Y key is pressed (event)!");
			BT_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
	private:
		std::shared_ptr<Brute::VertexArray> m_VertexArray;
		std::shared_ptr<Brute::Shader> m_Shader;
};

class Sandbox : public Brute::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Brute::Application* Brute::CreateApplication()
{
	return new Sandbox();
}