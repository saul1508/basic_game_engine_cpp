//** \file keyEvents.h */
#pragma once

#include "event.h"

namespace Engine {

	/** \class KeyPressEvent */

	class KeyPressEvent : public Event {
		public:
			KeyPressEvent(uint32_t keyCode, uint32_t repeatCount) : Event(EventType::KeyPress, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput),
				m_keyCode(keyCode), m_repeatCount(repeatCount) { } // KeyPressEvent constructor
			uint32_t getKeyCode() { return m_keyCode; } //!< Gets keycode
			uint32_t getRepeatCount() { return m_repeatCount; } //!< Getter methof for repeat count
		protected:
			uint32_t m_keyCode; //!< Key code attribute
			uint32_t m_repeatCount; //!< Repeat count attribute
	};

	/** \class KeyReleaseEvent */

	class KeyReleaseEvent : public Event {
		public:
			KeyReleaseEvent(uint32_t keyCode) : Event(EventType::KeyRealease, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput),
				m_keyCode(keyCode) { } //!< KeyReleaseEvent constructor
			uint32_t getKeyCode() { return m_keyCode; } //!< Getter method for keycode
		protected:
			uint32_t m_keyCode; //!< Key code attribute
	};

	/** \class KeyTypeEvent */

	class KeyTypeEvent : public Event {
		public:
			KeyTypeEvent(uint32_t keyCode) : Event(EventType::KeyType, EventCategory::EventCategoryKeyboard | EventCategory::EventCategoryInput), 
				m_keyCode(keyCode) { } //!< KeyTypeEvent constructor
			uint32_t getKeyCode() { return m_keyCode; } //!< Getter method for keycode
		protected:
			uint32_t m_keyCode; //!< Key code attribute
	};
}
