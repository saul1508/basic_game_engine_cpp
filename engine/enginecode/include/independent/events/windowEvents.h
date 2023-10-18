//** \file windowEvents.h */
#pragma once

#include "event.h"

namespace Engine {

	/** \class WindowCloseEvent */

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() { //!< WindowCloseEvent constructor
			m_eventType = EventType::WindowClose; 
			m_categoryFlags = EventCategory::EventCategoryWindow | EventCategory::EventCategoryInput;
		}
		
	};

	/** \class WindowResizeEvent */

	class WindowResizeEvent : public Event {
		public:
			WindowResizeEvent(int32_t width, int32_t height) : Event(EventType::WindowResize, EventCategory::EventCategoryWindow | EventCategory::EventCategoryInput),
				m_width(width), m_height(height) { } //!< WindowResizeEvent constructor
			int32_t getWidth() { return m_width; } //!< Getter method for width
			int32_t getHeight() { return m_height; } //!< Getter methof got height
		protected:
			int32_t m_width; //!< Width attribute
			int32_t m_height; //!< Height attribute
	};

	/** \class WindowFocusEvent */

	class WindowFocusEvent : public Event {
		public:
			WindowFocusEvent() { //!< WindowFocusEvent constructor
				m_eventType = EventType::WindowFocus;
				m_categoryFlags = EventCategory::EventCategoryWindow | EventCategory::EventCategoryInput;
			}
	};

	/** \class WindowLoseFocusEvent */

	class WindowLoseFocusEvent : public Event { 
		public:
			WindowLoseFocusEvent() { //!< WindowLoseFocusEvent constructor
				m_eventType = EventType::WindowLoseFocus;
				m_categoryFlags = EventCategory::EventCategoryWindow | EventCategory::EventCategoryInput;
			}
	};

	/** \class WindowMoveEvent */

	class WindowMoveEvent : public Event {
		public:
			WindowMoveEvent(int32_t newXPos, int32_t newYPos) : Event(EventType::WindowMove, EventCategory::EventCategoryWindow | EventCategory::EventCategoryInput),
				m_newXPos(newXPos), m_newYPos(newYPos) { } //!< WindowMoveEvent constructor
			int32_t getNewXPos() { return m_newXPos; } //!< Getter method for new x position
			int32_t getNewYPos() { return m_newYPos; } //!< Getter method for new y position
		protected:
			int32_t m_newXPos; //!< New x position attribute
			int32_t m_newYPos; //!< New y position attribute
	};
}



