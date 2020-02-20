#include <Brute.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Brute::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), 
		m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), 
		m_CameraPosition(0.0f), m_CameraRotation(0.0f),
		m_SquarePosition(0.0f)
	{
		// Vertex Array
		// Vertex Buffer
		// Index Buffer
		// Shader

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

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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

		////// RENDER SQUARE //////

		m_SquareVA.reset(Brute::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<Brute::VertexBuffer> squareVB;
		squareVB.reset(Brute::VertexBuffer::Create(
			squareVertices, sizeof(squareVertices)
		));

		squareVB->SetLayout({
			{ Brute::ShaderDataType::Float3, "a_Position" },
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Brute::IndexBuffer> squareIB;
		squareIB.reset(Brute::IndexBuffer::Create(
			squareIndices, sizeof(squareIndices) / sizeof(uint32_t)
		));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string blueShaderVertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_ShaderBlue.reset(Brute::Shader::Create(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Brute::TimeStep ts) override
	{
		//BT_TRACE("Delta time: {0}", ts.GetSeconds());
		/*if (Brute::Input::IsKeyPressed(BT_KEY_Y))
			BT_TRACE("Y key is pressed (poll)!");*/

		if (Brute::Input::IsKeyPressed(BT_KEY_LEFT))
				m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Brute::Input::IsKeyPressed(BT_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Brute::Input::IsKeyPressed(BT_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Brute::Input::IsKeyPressed(BT_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Brute::Input::IsKeyPressed(BT_KEY_A))
			m_CameraRotation += m_CameraRotateSpeed * ts;
		else if (Brute::Input::IsKeyPressed(BT_KEY_D))
			m_CameraRotation -= m_CameraRotateSpeed * ts;

		//------------------------------------------------//

		if (Brute::Input::IsKeyPressed(BT_KEY_J))
			m_SquarePosition.x -= m_SquareMoveSpeed * ts;
		else if (Brute::Input::IsKeyPressed(BT_KEY_L))
			m_SquarePosition.x += m_SquareMoveSpeed * ts;

		if (Brute::Input::IsKeyPressed(BT_KEY_I))
			m_SquarePosition.y += m_SquareMoveSpeed * ts;
		else if (Brute::Input::IsKeyPressed(BT_KEY_K))
			m_SquarePosition.y -= m_SquareMoveSpeed * ts;

		Brute::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Brute::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Brute::Renderer::BeginScene(m_Camera);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_SquarePosition);

		Brute::Renderer::Submit(m_ShaderBlue, m_SquareVA, transform);
		Brute::Renderer::Submit(m_Shader, m_VertexArray);

		Brute::Renderer::EndScene();
	}

	void OnImGuiRender() override {
		/*ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();*/
	}

	void OnEvent(Brute::Event& event) override
	{
		/*if (event.GetEventType() == Brute::EventType::KeyPressed)
		{
			Brute::KeyPressedEvent& e = (Brute::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BT_KEY_Y)
				BT_TRACE("Y key is pressed (event)!");
			BT_TRACE("{0}", (char)e.GetKeyCode());
		}*/

		//Brute::EventDispatcher dispatcher(event);
		//dispatcher.Dispatch<Brute::KeyPressedEvent>(BT_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
	}

	bool OnKeyPressedEvent(Brute::KeyPressedEvent& event) 
	{
		return false;
	}
private:
	std::shared_ptr<Brute::VertexArray> m_VertexArray;
	std::shared_ptr<Brute::Shader> m_Shader;

	std::shared_ptr<Brute::VertexArray> m_SquareVA;
	std::shared_ptr<Brute::Shader> m_ShaderBlue;

	Brute::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation;
	float m_CameraMoveSpeed = 5.0f;
	float m_CameraRotateSpeed = 180.0f;

	glm::vec3 m_SquarePosition;
	float m_SquareMoveSpeed = 1.0f;
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