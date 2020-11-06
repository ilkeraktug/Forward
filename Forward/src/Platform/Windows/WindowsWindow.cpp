#include "fwpch.h"

#include "WindowsWindow.h"

#include "Forward\Events\ApplicationEvent.h"
#include "Forward\Events\KeyEvent.h"
#include "Forward\Events\MouseEvent.h"

#include <GLFW\glfw3.h>
#include <glad\glad.h>

namespace Forward {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error_code, const char* description)
	{
		FW_CORE_ERROR("GLFW Error Code ({0}) : {1}", error_code, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enable;
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		
		FW_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int succes = glfwInit();
			FW_ASSERT(succes, "Can't initialized GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}
		//GLFW callbacks
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		FW_ASSERT(status, "Failed to initialize GLAD!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent e(width, height);
			data.EventCallback(e);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEvent e;
			data.EventCallback(e);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mod)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent e(key, 0);
					data.EventCallback(e);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent e(key, 1);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent e(key);
					data.EventCallback(e);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent e(button);
					data.EventCallback(e);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent e(button);
					data.EventCallback(e);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseScrollEvent e(xoffset, yoffset);
			data.EventCallback(e);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent e(xpos, ypos);
			data.EventCallback(e);
		}
		);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

}