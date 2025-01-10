#include <Dizzy.h>
#include "Dizzy/Core/EntryPoint.h"

class ExampleLayer : public Dizzy::Layer
{
public:
    ExampleLayer() : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        // DIZZY_INFO("ExampleLayer::Update");
    }

    void OnEvent(Dizzy::Event& event) override
    {
        DIZZY_TRACE("{0}", Dizzy::format_event(event));
    }
};


class Sandbox : public Dizzy::Application
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

Dizzy::Application* Dizzy::CreateApplication()
{
    return new Sandbox();
}
