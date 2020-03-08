#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	m_VertexArray = Brute::VertexArray::Create();

	float squareVertices[4 * 3] = {
		-0.5f, -0.5f, 0.0f,  // Bottom-Left  (black)
		 0.5f, -0.5f, 0.0f,  // Bottom-Right (red)
		 0.5f,  0.5f, 0.0f,  // Top-Right     (yellow)
		-0.5f,  0.5f, 0.0f   // Top-Left    (green)
	};

	Brute::Ref<Brute::VertexBuffer> squareVB;
	squareVB.reset(Brute::VertexBuffer::Create(
		squareVertices, sizeof(squareVertices)
	));

	squareVB->SetLayout({
		{ Brute::ShaderDataType::Float3, "a_Position" }
	});
	m_VertexArray->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Brute::Ref<Brute::IndexBuffer> squareIB;
	squareIB.reset(Brute::IndexBuffer::Create(
		squareIndices, sizeof(squareIndices) / sizeof(uint32_t)
	));
	m_VertexArray->SetIndexBuffer(squareIB);

	m_FlatColorShader = Brute::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Brute::TimeStep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Brute::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Brute::RenderCommand::Clear();

	Brute::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Brute::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Brute::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Brute::Renderer::Submit(m_FlatColorShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Brute::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Brute::Event& event)
{
	m_CameraController.OnEvent(event);
}
