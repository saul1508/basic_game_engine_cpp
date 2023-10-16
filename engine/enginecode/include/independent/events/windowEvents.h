//** \file windowEvents.h */
#pragma once

#include "event.h"

namespace Engine {

	/** \class WindowCloseEvent */

	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() : Event(EventType::WindowClose, EventCategory::EventCategoryWindow | EventCategory::EventCategoryInput) { }
		static EventType getStaticType() { return EventType::WindowClose; }
		virtual EventType getEventType() const override { return EventType::WindowClose; }
		virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
		
	};

	/** \class WindowResizeEvent */

	class WindowResizeEvent : public Event {
		public:
			WindowResizeEvent(int32_t width, int32_t height) : Event(EventType::WindowResize, EventCategory::EventCategoryWindow | EventCategory::EventCategoryInput),
				m_width(width), m_height(height) { }
			static EventType getStaticType() { return EventType::WindowResize; }
			virtual EventType getEventType() const override { return EventType::WindowResize; }
			virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
			int32_t getWidth() { return m_width; }
			int32_t getHeight() { return m_height; }
		protected:
			int32_t m_width;
			int32_t m_height;
	};

	/** \class WindowFocusEvent */

	class WindowFocusEvent : public Event {
		public:
			WindowFocusEvent() : Event(EventType::WindowFocus, EventCategory::EventCategoryWindow | EventCategory::EventCategoryInput) { }
			static EventType getStaticType() { return EventType::WindowFocus; }
			virtual EventType getEventType() const override { return EventType::WindowFocus; }
			virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};

	/** \class WindowLoseFocusEvent */

	class WindowLoseFocusEvent : public Event {
		public:
			WindowLoseFocusEvent() : Event(EventType::WindowLoseFocus, EventCategory::EventCategoryWindow | EventCategory::EventCategoryInput) { }
			static EventType getStaticType() { return EventType::WindowLoseFocus; }
			virtual EventType getEventType() const override { return EventType::WindowLoseFocus; }
			virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
	};

	/** \class WindowMoveEvent */

	class WindowMoveEvent : public Event {
		public:
			WindowMoveEvent(int32_t newXPos, int32_t newYPos) : Event(EventType::WindowMove, EventCategory::EventCategoryWindow | EventCategory::EventCategoryInput),
				m_newXPos(newXPos), m_newYPos(newYPos) { }
			static EventType getStaticType() { return EventType::WindowMove; }
			virtual EventType getEventType() const override { return EventType::WindowMove; }
			virtual int32_t getCategoryFlags() const override { return EventCategoryWindow; }
			int32_t getNewXPos() { return m_newXPos; }
			int32_t getNewYPos() { return m_newYPos; }
		protected:
			int32_t m_newXPos;
			int32_t m_newYPos;
	};
}



