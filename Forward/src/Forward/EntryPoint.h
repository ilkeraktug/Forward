#pragma once

#ifdef FW_PLATFORM_WINDOWS

extern Forward::Application* CreateApplication();

int main()
{
	auto app = CreateApplication();
	FW_INFO("Entry Point!");
	app->Run();
	delete app;
}

#endif // FW_PLATFORM_WINDOWS
