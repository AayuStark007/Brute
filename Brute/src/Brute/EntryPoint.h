#pragma once

#ifdef BT_PLATFORM_WINDOWS

extern Brute::Application* Brute::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Brute::CreateApplication();
	app->Run();
	delete app;
}

#endif
