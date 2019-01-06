#include <Brute.h>

class ExampleLayer : public Brute::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//BT_INFO("ExampleLayer::Update");
	}

	void OnEvent(Brute::Event& event) override
	{
		BT_TRACE("{0}", event);
	}
};

class Sandbox : public Brute::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Brute::Application* Brute::CreateApplication()
{
	return new Sandbox();
}