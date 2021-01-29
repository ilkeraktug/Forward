#include "fwpch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform\OpenGL\OpenGLShader.h"

namespace Forward {
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		FW_CORE_ASSERT(false, "Renderer API : None is selected!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		return nullptr;
	}
}
