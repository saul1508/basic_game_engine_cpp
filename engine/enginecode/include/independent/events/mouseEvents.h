/** \file mouseEvents.h */
#pragma once

#include "event.h"

namespace Engine {

	/** \class MouseButtonPressEvent */

	class MouseButtonPressEvent : public Event {
		public:
			MouseButtonPressEvent(uint32_t button) : Event(EventType::MouseButtonPress, EventCategory::EventCategoryMouseButton | EventCategory::EventCategoryInput),
				m_button(button) { } //!< MouseButtonPressEvent constructor
			uint32_t getButton() { return m_button; } //!< Getter method for button
		protected:
			uint32_t m_button; //!< Button attribute
	};

	/** \class MouseButtonReleaseEvent */

	class MouseButtonReleaseEvent : public Event {
		public:
			MouseButtonReleaseEvent(uint32_t button) : Event(EventType::MouseButtonRealease, EventCategory::EventCategoryMouseButton | EventCategory::EventCategoryInput),
				m_button(button) {} //!< MouseButtonReleasedEvent constructor
			uint32_t getButton() { return m_button; } //!< Getter method for button
		protected:
			uint32_t m_button; //!< Button attribute
	};

	/** \class MouseMoveEvent */

	class MouseMoveEvent : public Event {
	public:
		MouseMoveEvent(int32_t newXPos, int32_t newYPos) : Event(EventType::MouseMove, EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput),
			m_newXPos(newXPos), m_newYPos(newYPos) {} //!< MouseMoveEvent constructor
		int32_t getNewXPos() { return m_newXPos; } //!< Getter method for new x position
		int32_t getNewYPos() { return m_newYPos; } //!< Getter method for new y position
	protected:
		int32_t m_newXPos; //!< new x position attrbute
		int32_t m_newYPos; //!< new y position attribute
	};

	/** \class MouseScrollEvent */

	class MouseScrollEvent : public Event {
	public:
		MouseScrollEvent(int32_t offset) : Event(EventType::MouseScroll, EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput),
			m_offset(offset) {} //!< MouseScrollEvent constructor
		int32_t getOffset() { return m_offset; } //!< Getter method for offset
	protected:
		int32_t m_offset; //!< Offset attribute
	};

}
