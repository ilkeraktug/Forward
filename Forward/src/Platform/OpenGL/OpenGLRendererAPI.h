#pragma once

#include "Forward\Renderer\RendererAPI.h"

namespace Forward {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetClearColor(glm::vec4& color) override;
		virtual void Clear() override;
	
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	private:
	};
}