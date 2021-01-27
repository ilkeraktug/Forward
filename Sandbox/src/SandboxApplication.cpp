#include <Forward.h>

class ExampleLayer : public Forward::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.0f, 1.0f, -1.0f, 1.0f)
	{
		m_VertexArray.reset(Forward::VertexArray::Create());

		float vertices[] = {
			//Vertex Positions,		Colors
			-0.5f, -0.5f, 0.0f,		1.0f, 0.5f, 0.31f, 1.0f,
			 0.5f, -0.5f, 0.0f,		0.0f, 0.8f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f,		1.0f, 0.0f, 1.0f, 1.0f
		};

		std::shared_ptr<Forward::VertexBuffer> vertexBuffer;

		vertexBuffer.reset(Forward::VertexBuffer::Create(vertices, sizeof(vertices)));

		Forward::BufferLayout layout = {
			{ Forward::ShaderDataType::Float3, "a_Position" },
			{ Forward::ShaderDataType::Float4, "a_Color" },
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0, 1, 2 };
		std::shared_ptr<Forward::IndexBuffer> indexBuffer;
		indexBuffer.reset(Forward::IndexBuffer::Create(indices, 3));

		m_VertexArray->AddIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
		#version 330
	
		layout(location = 0) in vec4 a_Position;
		layout(location = 1) in vec4 a_Color;

		out vec4 v_Color;		
		uniform mat4 u_ViewProjection;		

		void main()
		{
			gl_Position = u_ViewProjection * a_Position;
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

		m_Shader.reset(new Forward::Shader(vertexSrc, fragmentSrc));
		//m_Camera.SetPosition({ -0.5f, 0.0f, 0.0f });
		m_Camera.SetRotation(-45.0f);
	}

	virtual void OnUpdate() override
	{
		Forward::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Forward::RenderCommand::Clear();

		{
			Forward::Renderer::BeginScene(m_Camera);

			Forward::Renderer::Submit(m_VertexArray, m_Shader);

			Forward::Renderer::EndScene();
		}

	}

private:

	std::shared_ptr<Forward::VertexArray> m_VertexArray;
	std::shared_ptr<Forward::Shader> m_Shader;

	Forward::OrthographicCamera m_Camera;
};


class Sandbox : public Forward::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox()
	{

	}
};

Forward::Application* CreateApplication()
{
	return new Sandbox();
}