#include "btpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Brute {

	Ref<VertexArray> VertexArray::Create()
	{
		// determine which api our renderer is using
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BT_CORE_ASSERT(false, "RendererAPI::API::None is curently not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();

		case RendererAPI::API::Direct3D:
			BT_CORE_ASSERT(false, "RendererAPI::API::Direct3D is curently not supported!");
			return nullptr;

		case RendererAPI::API::Vulkan:
			BT_CORE_ASSERT(false, "RendererAPI::API::Vulkan is curently not supported!");
			return nullptr;
		}

		BT_CORE_ASSERT(false, "Unknown RendererAP::APII!");
		return nullptr;
	}

}
