#pragma once

#ifdef DIZZY_PLATFORM_WINDOWS

extern Dizzy::Application* Dizzy::CreateApplication();

int main(int argc, char** argv)
{
    Dizzy::Logger::Init();
    DIZZY_CORE_WARN("Initialized Log");
    auto app = Dizzy::CreateApplication();
    app->Run();
    delete app;
}

#endif
