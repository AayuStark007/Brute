#include "btpch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

namespace Brute {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Brute::ShaderDataType::None:   return GL_FLOAT;
			case Brute::ShaderDataType::Float:  return GL_FLOAT;
			case Brute::ShaderDataType::Float2: return GL_FLOAT;
			case Brute::ShaderDataType::Float3: return GL_FLOAT;
			case Brute::ShaderDataType::Float4: return GL_FLOAT;
			case Brute::ShaderDataType::Mat3:   return GL_FLOAT;
			case Brute::ShaderDataType::Mat4:   return GL_FLOAT;
			case Brute::ShaderDataType::Int:    return GL_INT;
			case Brute::ShaderDataType::Int2:   return GL_INT;
			case Brute::ShaderDataType::Int3:   return GL_INT;
			case Brute::ShaderDataType::Int4:   return GL_INT;
			case Brute::ShaderDataType::Bool:   return GL_BOOL;
		}

		BT_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Brute::Ref<VertexBuffer>& vertexBuffer)
	{
		BT_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index + m_VertexBufferIndexOffset);
			glVertexAttribPointer(
				index + m_VertexBufferIndexOffset,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset
			);
			index++;
			m_VertexBufferIndexOffset += layout.GetElements().size();
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Brute::Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}
