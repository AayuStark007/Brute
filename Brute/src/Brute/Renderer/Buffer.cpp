#include "btpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Brute {

	VertexBuffer* VertexBuffer::Create(float * vertices, uint32_t size)
	{
		// determine which api our renderer is using
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:   
				BT_CORE_ASSERT(false, "RendererAPI::API::None is curently not supported!"); 
				return nullptr;

			case RendererAPI::API::OpenGL: 
				return new OpenGLVertexBuffer(vertices, size);

			case RendererAPI::API::Direct3D:
				BT_CORE_ASSERT(false, "RendererAPI::API::Direct3D is curently not supported!");
				return nullptr;

			case RendererAPI::API::Vulkan:
				BT_CORE_ASSERT(false, "RendererAPI::API::Vulkan is curently not supported!");
				return nullptr;
		}

		BT_CORE_ASSERT(false, "Unknown RendererAPI::API!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t * indices, uint32_t count)
	{
		// determine which api our renderer is using
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BT_CORE_ASSERT(false, "RendererAPI::API::None is curently not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLIndexBuffer(indices, count);

		case RendererAPI::API::Direct3D:
			BT_CORE_ASSERT(false, "RendererAPI::API::Direct3D is curently not supported!");
			return nullptr;

		case RendererAPI::API::Vulkan:
			BT_CORE_ASSERT(false, "RendererAPI::API::Vulkan is curently not supported!");
			return nullptr;
		}

		BT_CORE_ASSERT(false, "Unknown RendererAPI::API!");
		return nullptr;
	}

}