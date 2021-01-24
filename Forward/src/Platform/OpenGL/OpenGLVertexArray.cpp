#include "fwpch.h"
#include "OpenGLVertexArray.h"

#include <glad\glad.h>

namespace Forward {


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

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		FW_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Layout is empty!");

		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
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

		m_VertexBuffers.push_back(vertexBuffer);

	}

	void OpenGLVertexArray::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
}