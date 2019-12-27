#include "btpch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Brute {

	Shader* Shader::Create(const std::string & vertexSrc, const std::string & fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			BT_CORE_ASSERT(false, "RendererAPI::None is curently not supported!");
			return nullptr;

		case RendererAPI::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);

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