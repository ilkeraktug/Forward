#pragma once

#include "Forward\Renderer\GraphicsContext.h"

struct GLFWwindow;

namespace Forward {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_Window;
	};
}