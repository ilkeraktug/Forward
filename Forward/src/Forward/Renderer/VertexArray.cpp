#include "fwpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform\OpenGL\OpenGLVertexArray.h"

namespace Forward {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		FW_CORE_ASSERT(false, "Renderer API : None is selected!"); return nullptr;
		case RendererAPI::API::OpenGL:		return new OpenGLVertexArray();
		}

		return nullptr;
	}

}
