#pragma once

#include "dzpch.h"
#include "Core/Core.h"
#include "Events/Event.h"

// Dizzy和窗口界面的接口
namespace Dizzy {

    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;
        // 构造函数初始化
        explicit WindowProps(const std::string& title = "Dizzy Engine",
                    unsigned int width = 1920,
                    unsigned int height = 1080)
            : Title(title), Width(width), Height(height)
        {
        }    
    };

    // Interface representing a desktop system based Window
    class DIZZY_API Window
    {
    public:
        using EventCallbackFunc = std::function<void(Event&)>;
        virtual ~Window() = default;
        virtual void OnUpdate() = 0;
        [[nodiscard]] virtual unsigned int GetWidth() const = 0;
        [[nodiscard]] virtual unsigned int GetHeight() const = 0;
        // Window attributes
        virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        [[nodiscard]] virtual bool IsVSync() const = 0;
        // 设置为静态的原因：我们只希望用到一个实例来创建所有窗口
        static Window* Create(const WindowProps& props = WindowProps());
    };
    
}