#include "btpch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Brute {



	Ref<Texture2D> Texture2D::Create(const std::string & path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BT_CORE_ASSERT(false, "RendererAPI::API::None is curently not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLTexture2D>(path);

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
