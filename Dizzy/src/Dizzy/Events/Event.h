#pragma once

namespace Dizzy
{
    enum class EventType
    {
        None = 0,
        // Window Event
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,
        // App Event
        AppTick,
        AppUpdate,
        AppRender,
        // Keyboard Event
        KeyPressed,
        KeyReleased,
        // Mouse Event
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };


#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }\
virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class DIZZY_API Event
    {
    public:
        virtual ~Event() = default;
        [[nodiscard]] virtual EventType GetEventType() const = 0;
        [[nodiscard]] virtual const char* GetName() const = 0;
        [[nodiscard]] virtual int GetCategoryFlags() const { return 0; }
        [[nodiscard]] virtual std::string ToString() const { return GetName(); }

        [[nodiscard]] bool IsInCategory(EventCategory category) const
        {
            return GetCategoryFlags() & category;
        }

        bool Handled = false;
    };

    class EventDispatcher
    {
        template <typename T>
        using EventFn = std::function<bool(T&)>;

    public:
        explicit EventDispatcher(Event& event)
            : m_Event(event)
        {
        }

        template <typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.Handled = func(*static_cast<T*>(&m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    inline std::string format_event(const Event& e)
    {
        return e.ToString();
    }
}
