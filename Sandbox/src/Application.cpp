#include <Forward.h>

class Sandbox : public Forward::Application {
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}
};

Forward::Application* CreateApplication()
{
	return new Sandbox();
}