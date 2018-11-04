#include <Brute.h>

class Sandbox : public Brute::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}

};

Brute::Application* Brute::CreateApplication()
{
	return new Sandbox();
}