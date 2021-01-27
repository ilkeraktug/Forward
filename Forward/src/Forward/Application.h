#pragma once

#include "Core.h"

#include "Window.h"
#include "Forward\LayerStack.h"

#include "Forward\Events\ApplicationEvent.h"
#include "Forward\Events\KeyEvent.h"
#include "Forward\Events\MouseEvent.h"
#include "Forward\ImGui\ImGuiLayer.h"

#include "Platform\OpenGL\OpenGLBuffer.h"
#include "Platform\OpenGL\OpenGLVertexArray.h"

#include "Forward\Renderer\Shader.h"
#include "Forward\Renderer\OrthographicCamera.h"

namespace Forward {
	class FORWARD_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowsClose(WindowCloseEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		LayerStack m_LayerStack;

		bool m_Running = true;

		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
	};
}