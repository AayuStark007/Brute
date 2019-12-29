#include "btpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Brute {

	VertexArray* VertexArray::Create()
	{
		// determine which api our renderer is using
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			BT_CORE_ASSERT(false, "RendererAPI::None is curently not supported!");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();

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
