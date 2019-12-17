#include <Brute.h>

#include "imgui/imgui.h"

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

		if (Brute::Input::IsKeyPressed(BT_KEY_Y))
			BT_TRACE("Y key is pressed (poll)!");
	}

	void OnImGuiRender() override {
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Brute::Event& event) override
	{
		//BT_TRACE("{0}", event);
		if (event.GetEventType() == Brute::EventType::KeyPressed)
		{
			Brute::KeyPressedEvent& e = (Brute::KeyPressedEvent&)event;
			if (e.GetKeyCode() == BT_KEY_Y)
				BT_TRACE("Y key is pressed (event)!");
			BT_TRACE("{0}", (char)e.GetKeyCode());
		}
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