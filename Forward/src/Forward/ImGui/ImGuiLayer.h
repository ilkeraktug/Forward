#pragma once

#include "Forward\Core.h"

#include "Forward\Layer.h"
#include "Forward\Events\MouseEvent.h"

namespace Forward {

	class FORWARD_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		virtual ~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}