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
			case RendererAPI::None:   
				BT_CORE_ASSERT(false, "RendererAPI::None is curently not supported!"); 
				return nullptr;

			case RendererAPI::OpenGL: 
				return new OpenGLVertexBuffer(vertices, size);

			case RendererAPI::Direct3D:
				BT_CORE_ASSERT(false, "RendererAPI::Direct3D is curently not supported!");
				return nullptr;

			case RendererAPI::Vulkan:
				BT_CORE_ASSERT(false, "RendererAPI::Vulkan is curently not supported!");
				return nullptr;
		}

		BT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t * indices, uint32_t count)
	{
		// determine which api our renderer is using
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			BT_CORE_ASSERT(false, "RendererAPI::None is curently not supported!");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);

		case RendererAPI::Direct3D:
			BT_CORE_ASSERT(false, "RendererAPI::Direct3D is curently not supported!");
			return nullptr;

		case RendererAPI::Vulkan:
			BT_CORE_ASSERT(false, "RendererAPI::Vulkan is curently not supported!");
			return nullptr;
		}

		BT_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}