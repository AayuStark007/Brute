#include "btpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>


namespace Brute {

	OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		: m_windowHandle(windowHandle)
	{
		BT_CORE_ASSERT(windowHandle, "Window Handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_windowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BT_CORE_ASSERT(status, "Failed to initialize Glad!");

		BT_CORE_INFO("OpenGL Info");
		BT_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		BT_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		BT_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

	#ifdef BT_ENABLE_ASSERTS
		int majorVersion, minorVersion;
		glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
		glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

		BT_CORE_ASSERT(majorVersion > 4 || (majorVersion == 4 && minorVersion >= 5), "Required atleast OpenGL version 4.5!")
	#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_windowHandle);
	}

}