#pragma once

#include "Event.h"

namespace Dizzy
{
    class DIZZY_API KeyEvent : public Event
    {
    public:
        [[nodiscard]] inline int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        explicit KeyEvent(int keyCode): m_KeyCode(keyCode)
        {
        }

        int m_KeyCode;
    };

    class DIZZY_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_RepeatCount(repeatCount)
        {
        }

        [[nodiscard]] inline int GetRepeatCount() const { return m_RepeatCount; }

        [[nodiscard]] std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        int m_RepeatCount;
    };

    class DIZZY_API KeyReleasedEvent : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(int keyCode) : KeyEvent(keyCode)
        {
        }

        [[nodiscard]] std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };
}
