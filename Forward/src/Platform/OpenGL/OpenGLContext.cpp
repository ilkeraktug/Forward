#include "fwpch.h"
#include "OpenGLContext.h"

#include "GLFW\glfw3.h"
#include <glad\glad.h>

namespace Forward {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_Window(windowHandle)
	{
		FW_CORE_ASSERT(m_Window, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FW_CORE_ASSERT(status, "Failed to initialize GLAD!");

		FW_CORE_INFO("OpenGL Info : ");
		FW_CORE_INFO("\tVendor   : {0}", glGetString(GL_VENDOR));
		FW_CORE_INFO("\tRenderer : {0}", glGetString(GL_RENDERER));
		FW_CORE_INFO("\tVersion  : {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

}