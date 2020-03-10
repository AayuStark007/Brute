#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{

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

	Brute::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Brute::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Brute::Renderer2D::EndScene();

	//Brute::Renderer2D::Submit(m_FlatColorShader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	//std::dynamic_pointer_cast<Brute::OpenGLShader>(m_FlatColorShader)->Bind();
	//std::dynamic_pointer_cast<Brute::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);
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
