//** \file keyEvents.h */
#pragma once

#include "event.h"

namespace Engine {

	/** \class KeyPressEvent */

	class KeyPressEvent : public Event {
		public:
			KeyPressEvent(uint32_t keyCode, uint32_t repeatCount) : Event(EventType::KeyPress, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput),
				m_keyCode(keyCode), m_repeatCount(repeatCount) { }
			//static EventType getStaticType() { return EventType::KeyPress; }
			//EventType getEventType() const { return EventType::KeyPress; }
			//int32_t getCategoryFlags() const { return EventCategoryKeyboard; }
			uint32_t getKeyCode() { return m_keyCode; }
			uint32_t getRepeatCount() { return m_repeatCount; }
		protected:
			uint32_t m_keyCode;
			uint32_t m_repeatCount;
	};

	/** \class KeyReleaseEvent */

	class KeyReleaseEvent : public Event {
		public:
			KeyReleaseEvent(uint32_t keyCode, uint32_t repeatCount) : Event(EventType::KeyRealease, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput),
				m_keyCode(keyCode), m_repeatCount(repeatCount) { }
			//static EventType getStaticType() { return EventType::KeyRealease; }
			//EventType getEventType() const { return EventType::KeyRealease; }
			//int32_t getCategoryFlags() const { return EventCategoryKeyboard; }
			uint32_t getKeyCode() { return m_keyCode; }
			uint32_t getRepeatCount() { return m_repeatCount; }
		protected:
			uint32_t m_keyCode;
			uint32_t m_repeatCount;
	};

	/** \class KeyTypeEvent */

	class KeyTypeEvent : public Event {
		public:
			KeyTypeEvent(uint32_t keyCode, uint32_t repeatCount) : Event(EventType::KeyType, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput),
				m_keyCode(keyCode) { }
			//static EventType getStaticType() { return EventType::KeyType; }
			//EventType getEventType() const { return EventType::KeyType; }
			//int32_t getCategoryFlags() const { return EventCategoryKeyboard; }
			uint32_t getKeyCode() { return m_keyCode; }
		protected:
			uint32_t m_keyCode;
	};
}
