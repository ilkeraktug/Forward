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
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_Window);
	}

}