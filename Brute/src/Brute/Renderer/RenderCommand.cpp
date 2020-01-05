#include "btpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Brute {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}