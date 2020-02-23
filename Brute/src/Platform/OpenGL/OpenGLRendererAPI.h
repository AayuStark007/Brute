#pragma once

#include "Brute/Renderer/RendererAPI.h"

namespace Brute {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Brute::Ref<VertexArray>& vertexArray) override;
	};

}
