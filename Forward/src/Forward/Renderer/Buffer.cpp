#include "fwpch.h"
#include "Buffer.h"

#include "Forward\Renderer\Renderer.h"
#include "Platform\OpenGL\OpenGLBuffer.h"

namespace Forward {
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		FW_CORE_ASSERT(false, "Renderer API : None is selected!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLVertexBuffer(vertices, size);
		}

		FW_CORE_ASSERT(false, "Unknown API!"); return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:		FW_CORE_ASSERT(false, "Renderer API : None is selected!"); return nullptr;
		case RendererAPI::API::OpenGL:	return new OpenGLIndexBuffer(indices, count);
		}

		FW_CORE_ASSERT(false, "Unknown API!"); return nullptr;
	}
}