#pragma once

#ifdef BT_PLATFORM_WINDOWS

extern Brute::Application* Brute::CreateApplication();

int main(int argc, char** argv)
{

	Brute::Log::Init();
	BT_CORE_WARN("Initialized Log!");
	//int a = 78;
	//BT_INFO("Hello!{0}", a);
	//BT_CORE_INFO("Hello!{0}", a);

	auto app = Brute::CreateApplication();
	app->Run();
	delete app;
}

#endif
