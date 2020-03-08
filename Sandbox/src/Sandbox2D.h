#pragma once

#include <Brute.h>
#include <Platform/OpenGL/OpenGLShader.h>

#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Sandbox2D : public Brute::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Brute::TimeStep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Brute::Event& event) override;
private:
	Brute::OrthographicCameraController m_CameraController;

	// Temp - (not needed in 2D Renderer)
	Brute::Ref<Brute::VertexArray> m_VertexArray;
	Brute::Ref<Brute::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};