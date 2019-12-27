#pragma once

#include "Brute/Renderer/Shader.h"

namespace Brute {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;
	private:
		uint32_t m_RendererID;
	};

}
