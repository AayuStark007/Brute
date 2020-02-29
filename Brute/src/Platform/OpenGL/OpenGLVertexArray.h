#pragma once

#include "Brute/Renderer/VertexArray.h"

namespace Brute {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray(); 

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Brute::Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Brute::Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Brute::Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
		virtual const Brute::Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };
	private:
		uint32_t m_RendererID;
		uint32_t m_VertexBufferIndex = 0;

		std::vector<Brute::Ref<VertexBuffer>> m_VertexBuffers;
		Brute::Ref<IndexBuffer> m_IndexBuffer;
	};

}
