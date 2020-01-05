#include "btpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Brute {

	Shader* Shader::Create(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			BT_CORE_ASSERT(false, "RendererAPI::API::None is curently not supported!");
			return nullptr;

		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);

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