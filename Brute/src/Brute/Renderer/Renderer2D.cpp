#include "btpch.h"

#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

namespace Brute {

	struct Renderer2DContext
	{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> flatColorShader;
	};

	static Renderer2DContext* s_Context;

	void Renderer2D::Init()
	{
		s_Context = new Renderer2DContext();

		s_Context->quadVertexArray = VertexArray::Create();

		float squareVertices[4 * 3] = {
			-0.5f, -0.5f, 0.0f,  // Bottom-Left  (black)
			 0.5f, -0.5f, 0.0f,  // Bottom-Right (red)
			 0.5f,  0.5f, 0.0f,  // Top-Right     (yellow)
			-0.5f,  0.5f, 0.0f   // Top-Left    (green)
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(
			squareVertices, sizeof(squareVertices)
		));

		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});
		s_Context->quadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(
			squareIndices, sizeof(squareIndices) / sizeof(uint32_t)
		));
		s_Context->quadVertexArray->SetIndexBuffer(squareIB);

		s_Context->flatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete s_Context;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Context->flatColorShader->Bind();
		s_Context->flatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
		s_Context->flatColorShader->SetMat4("u_Transform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Context->flatColorShader->Bind();
		s_Context->flatColorShader->SetFloat4("u_Color", color);

		s_Context->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Context->quadVertexArray);
	}

}
