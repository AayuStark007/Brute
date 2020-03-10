#include <Brute.h>
#include <Brute/Core/EntryPoint.h>

#include <Platform/OpenGL/OpenGLShader.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"


class ExampleLayer : public Brute::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f, true)
	{
		// Vertex Array
		// Vertex Buffer
		// Index Buffer
		// Shader

		m_VertexArray = Brute::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Brute::Ref<Brute::VertexBuffer> triangleVB;
		triangleVB.reset(Brute::VertexBuffer::Create(vertices, sizeof(vertices)));
		Brute::BufferLayout layout = {
			{ Brute::ShaderDataType::Float3, "a_Position" },
			{ Brute::ShaderDataType::Float4, "a_Color" }
		};
		triangleVB->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(triangleVB);

		uint32_t indices[3] = { 0, 1, 2 };
		Brute::Ref<Brute::IndexBuffer> triangleIB;
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

		m_Shader = Brute::Shader::Create("VertPosColor", vertexSrc, fragmentSrc);

		////// RENDER SQUARE //////

		m_SquareVA = Brute::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Bottom-Left  (black)
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Bottom-Right (red)
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // Top-Right     (yellow)
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f   // Top-Left    (green)
		};

		Brute::Ref<Brute::VertexBuffer> squareVB;
		squareVB.reset(Brute::VertexBuffer::Create(
			squareVertices, sizeof(squareVertices)
		));

		squareVB->SetLayout({
			{ Brute::ShaderDataType::Float3, "a_Position" },
			{ Brute::ShaderDataType::Float2, "a_TexCoord" },
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Brute::Ref<Brute::IndexBuffer> squareIB;
		squareIB.reset(Brute::IndexBuffer::Create(
			squareIndices, sizeof(squareIndices) / sizeof(uint32_t)
		));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string flatColorShaderVertexSrc = R"(
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

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		m_ShaderFlatColor = Brute::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Brute::Texture2D::Create("assets/textures/Checkerboard.png");
		m_BruteLogoTexture = Brute::Texture2D::Create("assets/textures/Logo.png");

		textureShader->Bind();
		textureShader->SetInt("u_Texture", 0);
	}

	void OnUpdate(Brute::TimeStep ts) override
	{
		//BT_TRACE("Delta time: {0}", ts.GetSeconds());
		/*if (Brute::Input::IsKeyPressed(BT_KEY_Y))
			BT_TRACE("Y key is pressed (poll)!");*/

		// Update
		m_CameraController.OnUpdate(ts);


		// Render
		Brute::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Brute::RenderCommand::Clear();

		Brute::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Brute::OpenGLShader>(m_ShaderFlatColor)->Bind();
		std::dynamic_pointer_cast<Brute::OpenGLShader>(m_ShaderFlatColor)->UploadUniformFloat3("u_Color", m_SquareColor);
		
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Brute::Renderer::Submit(m_ShaderFlatColor, m_SquareVA, transform);
			}
		}
		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Brute::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		m_BruteLogoTexture->Bind();
		Brute::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		
		// Triangle
		//Brute::Renderer::Submit(m_Shader, m_VertexArray);

		Brute::Renderer::EndScene();
	}

	void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Brute::Event& event) override
	{
		m_CameraController.OnEvent(event);
	}
private:
	Brute::ShaderLibrary m_ShaderLibrary;
	Brute::Ref<Brute::VertexArray> m_VertexArray;
	Brute::Ref<Brute::Shader> m_Shader;

	Brute::Ref<Brute::VertexArray> m_SquareVA;
	Brute::Ref<Brute::Shader> m_ShaderFlatColor;

	Brute::Ref<Brute::Texture2D> m_Texture;
	Brute::Ref<Brute::Texture2D> m_BruteLogoTexture;

	Brute::OrthographicCameraController m_CameraController;

	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Brute::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{

	}

};

Brute::Application* Brute::CreateApplication()
{
	return new Sandbox();
}