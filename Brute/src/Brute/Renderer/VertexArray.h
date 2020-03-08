#pragma once

#include <memory>

#include "Brute/Renderer/Buffer.h"

namespace Brute {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const Brute::Ref<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Brute::Ref<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<Brute::Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Brute::Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();
	};

}
