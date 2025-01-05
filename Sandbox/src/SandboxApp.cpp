
#include <Dizzy.h>

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
