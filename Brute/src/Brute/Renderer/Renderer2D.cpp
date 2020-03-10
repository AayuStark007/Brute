#include "btpch.h"

#include "Renderer2D.h"
#include "VertexArray.h"
#include "Shader.h"
#include "RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Brute {

	struct Renderer2DContext
	{
		Ref<VertexArray> quadVertexArray;
		Ref<Shader> flatColorShader;
		Ref<Shader> textureShader;
	};

	static Renderer2DContext* s_Context;

	void Renderer2D::Init()
	{
		s_Context = new Renderer2DContext();

		s_Context->quadVertexArray = VertexArray::Create();

		float squareVertices[4 * 5] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // Bottom-Left  (black)
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Bottom-Right (red)
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,  // Top-Right     (yellow)
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f   // Top-Left    (green)
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(
			squareVertices, sizeof(squareVertices)
		));

		squareVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		s_Context->quadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(
			squareIndices, sizeof(squareIndices) / sizeof(uint32_t)
		));
		s_Context->quadVertexArray->SetIndexBuffer(squareIB);

		s_Context->flatColorShader = Shader::Create("assets/shaders/FlatColor.glsl");
		s_Context->textureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Context->textureShader->Bind();
		s_Context->textureShader->SetInt("u_Texture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete s_Context;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Context->flatColorShader->Bind();
		s_Context->flatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_Context->textureShader->Bind();
		s_Context->textureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
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

		auto transform =
			glm::translate(glm::mat4(1.0f), position) * /* rotation */
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Context->flatColorShader->SetMat4("u_Transform", transform);

		s_Context->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Context->quadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture)
	{
		s_Context->textureShader->Bind();

		auto transform =
			glm::translate(glm::mat4(1.0f), position) * /* rotation */
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Context->textureShader->SetMat4("u_Transform", transform);

		texture->Bind();

		s_Context->quadVertexArray->Bind();
		RenderCommand::DrawIndexed(s_Context->quadVertexArray);
	}

}
