#pragma once

#include "Application.h"

#ifdef FW_PLATFORM_WINDOWS

extern Forward::Application* CreateApplication();

int main()
{
	auto app = CreateApplication();
	std::cout << "Forward!\n";
	app->Run();
	delete app;
}

#endif // FW_PLATFORM_WINDOWS
