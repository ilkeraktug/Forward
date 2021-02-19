#include <Forward.h>

#include <imgui\imgui.h>

#include <glm\gtx\transform.hpp>
#include <glm\gtc\type_ptr.hpp>

class ExampleLayer : public Forward::Layer
{
public:
	ExampleLayer()
		:Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f), m_TrianglePosition(0.0f)
	{
		m_VertexArray.reset(Forward::VertexArray::Create());

		float vertices[] = {
			//Vertex Positions,		TexCoords
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,		1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,		1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f
		};

		Forward::Ref<Forward::VertexBuffer> vertexBuffer;

		vertexBuffer.reset(Forward::VertexBuffer::Create(vertices, sizeof(vertices)));

		Forward::BufferLayout layout = {
			{ Forward::ShaderDataType::Float3, "a_Position" },
			{ Forward::ShaderDataType::Float2, "a_TexCoord" },
		};

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[] = { 0, 1, 2, 2, 3, 0};
		Forward::Ref<Forward::IndexBuffer> indexBuffer;
		indexBuffer.reset(Forward::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->AddIndexBuffer(indexBuffer);

		std::string vertexSrc = R"(
		#version 330
	
		layout(location = 0) in vec4 a_Position;
		layout(location = 1) in vec2 a_TexCoord;

		out vec2 v_TexCoord;		
		uniform mat4 u_ViewProjection;		
		uniform mat4 u_Transform;		

		void main()
		{
			gl_Position = u_ViewProjection * u_Transform * a_Position;
			v_TexCoord = a_TexCoord;
		})";

		std::string fragmentSrc = R"(
		#version 330
	
		layout(location = 0) out vec4 color;

		in vec2 v_TexCoord;
		uniform sampler2D u_Texture;

		void main()
		{
			//color = vec4(v_TexCoord, 0.0f, 1.0f);
			color = texture(u_Texture, v_TexCoord);
		})";

		m_Shader.reset(Forward::Shader::Create(vertexSrc, fragmentSrc));

		m_BoardTexture = Forward::Texture2D::Create("assets/textures/Checkerboard.png");
		m_LogoTexture = Forward::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Forward::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Forward::OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);
	}

	virtual void OnUpdate(Forward::Timestep ts) override
	{
		Forward::RenderCommand::SetClearColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		Forward::RenderCommand::Clear();

		if (Forward::Input::IsKeyPressed(FW_KEY_LEFT))
		{
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (Forward::Input::IsKeyPressed(FW_KEY_RIGHT))
		{
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		}

		if (Forward::Input::IsKeyPressed(FW_KEY_UP))
		{
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		}
		else if (Forward::Input::IsKeyPressed(FW_KEY_DOWN))
		{
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		}

		if (Forward::Input::IsKeyPressed(FW_KEY_E))
		{
			m_CameraRotation -= m_CameraRotationSpeed * ts;
		}
		else if (Forward::Input::IsKeyPressed(FW_KEY_Q))
		{
			m_CameraRotation += m_CameraRotationSpeed * ts;
		}

		if (Forward::Input::IsKeyPressed(FW_KEY_A))
		{
			m_TrianglePosition.x -= m_CameraMoveSpeed * ts;
		}
		else if (Forward::Input::IsKeyPressed(FW_KEY_D))
		{
			m_TrianglePosition.x += m_CameraMoveSpeed * ts;
		}

		if (Forward::Input::IsKeyPressed(FW_KEY_W))
		{
			m_TrianglePosition.y += m_CameraMoveSpeed * ts;
		}
		else if (Forward::Input::IsKeyPressed(FW_KEY_S))
		{
			m_TrianglePosition.y -= m_CameraMoveSpeed * ts;
		}
		
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		{
			Forward::Renderer::BeginScene(m_Camera);

			m_BoardTexture->Bind();
			Forward::Renderer::Submit(m_VertexArray, m_Shader, glm::scale(glm::vec3(1.5f)));

			m_LogoTexture->Bind();
			Forward::Renderer::Submit(m_VertexArray, m_Shader, glm::scale(glm::vec3(1.5f)));

			Forward::Renderer::EndScene();
		}

	}
	
	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorPicker4("Color", glm::value_ptr(m_Color));
		ImGui::End();
	}
private:

	Forward::Ref<Forward::VertexArray> m_VertexArray;
	Forward::Ref<Forward::Shader> m_Shader;

	Forward::Ref<Forward::Texture2D> m_BoardTexture, m_LogoTexture;

	Forward::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_TrianglePosition;
	glm::vec4 m_Color = { 0.2f, 0.6f, 0.8f, 1.0f };
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