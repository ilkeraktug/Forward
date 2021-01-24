#pragma once

#include "Forward\Renderer\RendererAPI.h"

namespace Forward {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(glm::vec4& color);
		virtual void Clear();
	
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray);
	private:
	};
}