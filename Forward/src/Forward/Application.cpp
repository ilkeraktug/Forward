#include "fwpch.h"
#include "Application.h"

#include "Forward\Log.h"
#include "Forward\Input.h"

#include "Renderer\Renderer.h"

namespace Forward {

	#define BIND_EVENT_FUNC(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FW_CORE_ASSERT(!s_Instance, "Already have an instatnce!");
		s_Instance = this;	

		Log::Init();
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNC(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

		float vertices[] = {
			//Vertex Positions,		Colors
			-0.5f, -0.5f, 0.0f,		1.0f, 0.5f, 0.31f, 1.0f,
			 0.5f, -0.5f, 0.0f,		0.0f, 0.8f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,		1.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;

		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
		};
		
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, 3));

		m_VertexArray->AddIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
		#version 330
	
		layout(location = 0) in vec4 a_Position;
		layout(location = 1) in vec4 a_Color;

		out vec4 v_Color;		

		void main()
		{
			gl_Position = a_Position;
			v_Color = a_Color;
		})";

		std::string fragmentSrc = R"(
		#version 330
	
		layout(location = 0) out vec4 color;

		in vec4 v_Color;

		void main()
		{
			color = vec4(1.0f, 0.5f, 0.31f, 1.0f);
			color = v_Color;
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
			RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
			RenderCommand::Clear();
			
			{
				Renderer::BeginScene();

				Renderer::Submit(m_VertexArray);

				Renderer::EndScene();
			}



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