#pragma once

#include "Brute/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Brute {

	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual void UploadUniformMat4(const std::string name, const glm::mat4& matrix) const;
	private:
		uint32_t m_RendererID;
	};

}
