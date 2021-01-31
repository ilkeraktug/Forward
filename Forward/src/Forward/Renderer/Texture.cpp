#include "fwpch.h"
#include "Texture.h"

#include "Renderer.h"

#include "Platform\OpenGL\OpenGLTexture2D.h"

namespace Forward {

	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		FW_CORE_ASSERT(false, "Renderer API : None is selected!"); return nullptr;
		case RendererAPI::API::OpenGL:		return std::make_shared<OpenGLTexture2D>(path);
		}

		return nullptr;
	}


}