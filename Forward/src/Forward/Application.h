#pragma once

#include "Core.h"

namespace Forward {
	class FORWARD_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
}