#include <Dizzy.h>
#include "Dizzy/Core/EntryPoint.h"

class Sandbox : public Dizzy::Application
{
public:
    Sandbox()
    {

    }

    ~Sandbox()
    {

    }
};

Dizzy::Application*  Dizzy::CreateApplication()
{
    return new Sandbox();
}
