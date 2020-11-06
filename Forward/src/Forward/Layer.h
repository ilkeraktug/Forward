#pragma once

#include "Forward\Core.h"
#include "Forward\Events\Event.h"

namespace Forward {

	class FORWARD_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");

		virtual ~Layer() = default;
		
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& e) {}

		inline std::string GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};

}