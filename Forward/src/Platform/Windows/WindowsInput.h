#pragma once

#include "Forward\Core.h"
#include "Forward\Input.h"

#include "Forward\Application.h"

namespace Forward {

	class FORWARD_API WindowsInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};
}