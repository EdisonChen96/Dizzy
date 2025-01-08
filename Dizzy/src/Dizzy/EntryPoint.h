#pragma once

#ifdef DIZZY_PLATFORM_WINDOWS

extern Dizzy::Application* Dizzy::CreateApplication();

inline int main(int argc, char** argv)
{
    Dizzy::Logger::Init();
    auto app = Dizzy::CreateApplication();
    app->Run();
    delete app;
}

#endif
