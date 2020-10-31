#include "fwpch.h"

#include "Application.h"

#include "Forward\Events\ApplicationEvent.h"
#include "Forward\Log.h"

#include <GLFW/glfw3.h>

namespace Forward {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application()
	{

	}

	void Application::Run()
	{
		FW_CORE_WARN("Creating window");
		while (m_Running)
		{
			glClearColor(1.0f, 0.5f, 0.31f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}