//** \file keyEvents.h */
#pragma once

#include "event.h"

namespace Engine {

	/** \class KeyPressEvent */

	class KeyPressEvent : public Event {
		public:
			KeyPressEvent(uint32_t keyCode, uint32_t repeatCount) : Event(EventType::KeyPress, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput),
				m_keyCode(keyCode), m_repeatCount(repeatCount) { }
			uint32_t getKeyCode() { return m_keyCode; }
			uint32_t getRepeatCount() { return m_repeatCount; }
		protected:
			uint32_t m_keyCode;
			uint32_t m_repeatCount;
	};

	/** \class KeyReleaseEvent */

	class KeyReleaseEvent : public Event {
		public:
			KeyReleaseEvent(uint32_t keyCode) : Event(EventType::KeyRealease, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput),
				m_keyCode(keyCode) { }
			uint32_t getKeyCode() { return m_keyCode; }
		protected:
			uint32_t m_keyCode;
	};

	/** \class KeyTypeEvent */

	class KeyTypeEvent : public Event {
		public:
			KeyTypeEvent(uint32_t keyCode) : Event(EventType::KeyType, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput),
				m_keyCode(keyCode) { }
			uint32_t getKeyCode() { return m_keyCode; }
		protected:
			uint32_t m_keyCode;
	};
}
