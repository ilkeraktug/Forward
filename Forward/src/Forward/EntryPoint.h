#pragma once

#ifdef FW_PLATFORM_WINDOWS

extern Forward::Application* CreateApplication();

int main()
{
	auto app = CreateApplication();
	Forward::Log::Init();
	FW_WARN("Hello!");
	app->Run();
	delete app;
}

#endif // FW_PLATFORM_WINDOWS
