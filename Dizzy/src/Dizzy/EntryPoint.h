#pragma once

#ifdef DIZZY_PLATFORM_WINDOWS

extern Dizzy::Application* Dizzy::CreateApplication();

int main(int argc, char** argv)
{
    printf("-- DizzyEngine Application Start --\n");
    auto app = Dizzy::CreateApplication();
    app->Run();
    delete app;
}

#endif
