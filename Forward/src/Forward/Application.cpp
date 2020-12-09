#include "fwpch.h"
#include "Application.h"

#include "Forward\Log.h"
#include "Forward\Input.h"

#include <GLFW/glfw3.h>
#include <glad\glad.h>

namespace Forward {

	#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Forward::ShaderDataType::Float:    return GL_FLOAT;
		case Forward::ShaderDataType::Float2:   return GL_FLOAT;
		case Forward::ShaderDataType::Float3:   return GL_FLOAT;
		case Forward::ShaderDataType::Float4:   return GL_FLOAT;
		case Forward::ShaderDataType::Mat3:     return GL_FLOAT;
		case Forward::ShaderDataType::Mat4:     return GL_FLOAT;
		case Forward::ShaderDataType::Int:      return GL_INT;
		case Forward::ShaderDataType::Int2:     return GL_INT;
		case Forward::ShaderDataType::Int3:     return GL_INT;
		case Forward::ShaderDataType::Int4:     return GL_INT;
		case Forward::ShaderDataType::Bool:     return GL_BOOL;
		}

		FW_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}


	Application::Application()
	{
		FW_CORE_ASSERT(!s_Instance, "Already have an instatnce!");
		s_Instance = this;	

		Log::Init();
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		{
			BufferLayout layout = {
				{ ShaderDataType::Float3, "a_Position" },
			};
		
			m_VertexBuffer->SetLayout(layout);
		}

		uint32_t index = 0;
		const auto& layout = m_VertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, 
				element.GetComponentCount(), 
				ShaderDataTypeToOpenGLBaseType(element.Type), 
				element.Normalized ? GL_TRUE : GL_FALSE, 
				layout.GetStride(), 
				(const void*)element.Offset);

			index++;
		}

		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		uint32_t indices[] = { 0, 1, 2 };

		m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

		std::string vertexSrc = R"(
		#version 330
	
		layout(location = 0) in vec4 a_Position;

		void main()
		{
			gl_Position = a_Position;
		})";

		std::string fragmentSrc = R"(
		#version 330
	
		layout(location = 0) out vec4 color;

		void main()
		{
			color = vec4(1.0f, 0.5f, 0.31f, 1.0f);
		})";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
		m_Shader->Bind();
	}
	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();

		}
	}

	void Application::OnEvent(Event& e)
	{
		//FW_CORE_TRACE("{0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNC(OnWindowsClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.m_Handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layer->OnAttach();
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		overlay->OnAttach();
		m_LayerStack.PushOverlay(overlay);
	}

	bool Application::OnWindowsClose(WindowCloseEvent& e)
	{
		m_Running = false;

		return true;
	}
}