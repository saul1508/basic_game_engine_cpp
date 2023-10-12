//** \file keyEvents.h */
#pragma once

#include "event.h"

namespace Engine {

	/** \class KeyPressedEvent */

	class KeyPressedEvent : public Event {
		public:
			KeyPressedEvent(uint32_t keyCode, uint32_t repeatCount) : Event(EventType::KeyPressed, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput),
				m_keyCode(keyCode), m_repeatCount(repeatCount) { }
			static EventType getStaticType() { return EventType::KeyPressed; }
			virtual EventType getEventType() const override { return EventType::KeyPressed; }
			virtual int32_t getCategoryFlags() const override { return EventCategoryKeyboard; }
			uint32_t getKeyCode() { return m_keyCode; }
			uint32_t getRepeatCount() { return m_repeatCount; }
		protected:
			uint32_t m_keyCode;
			uint32_t m_repeatCount;
	};

	/** \class KeyReleasedEvent */

	class KeyReleasedEvent : public Event {
		public:
			KeyReleasedEvent(uint32_t keyCode, uint32_t repeatCount) : Event(EventType::KeyRealeased, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput),
				m_keyCode(keyCode), m_repeatCount(repeatCount) { }
			static EventType getStaticType() { return EventType::KeyRealeased; }
			virtual EventType getEventType() const override { return EventType::KeyRealeased; }
			virtual int32_t getCategoryFlags() const override { return EventCategoryKeyboard; }
			uint32_t getKeyCode() { return m_keyCode; }
			uint32_t getRepeatCount() { return m_repeatCount; }
		protected:
			uint32_t m_keyCode;
			uint32_t m_repeatCount;
	};

	/** \class KeyTypedEvent */

	class KeyTypedEvent : public Event {
		public:
			KeyTypedEvent(uint32_t keyCode, uint32_t repeatCount) : Event(EventType::KeyTyped, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput),
				m_keyCode(keyCode) { }
			static EventType getStaticType() { return EventType::KeyTyped; }
			virtual EventType getEventType() const override { return EventType::KeyTyped; }
			virtual int32_t getCategoryFlags() const override { return EventCategoryKeyboard; }
			uint32_t getKeyCode() { return m_keyCode; }
		protected:
			uint32_t m_keyCode;
	};
}
