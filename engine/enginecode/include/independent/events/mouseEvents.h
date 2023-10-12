/** \file mouseEvents.h */
#pragma once

#include "event.h"

namespace Engine {

	/** \class MouseButtonPressedEvent */

	class MouseButtonPressedEvent : public Event {
		public:
			MouseButtonPressedEvent(uint32_t button) : Event(EventType::MouseButtonPressed, EventCategory::EventCategoryMouseButton | EventCategory::EventCategoryInput),
				m_button(button) { }
			uint32_t getButton() { return m_button; }
			static EventType getStaticType() { return EventType::MouseButtonPressed; }
			virtual EventType getEventType() const override { return EventType::MouseButtonPressed; }
			virtual int32_t getCategoryFlags() const override { return EventCategoryMouseButton; }
		protected:
			uint32_t m_button;
	};

	/** \class MouseButtonReleasedEvent */

	class MouseButtonReleasedEvent : public Event {
		public:
			MouseButtonReleasedEvent(uint32_t button) : Event(EventType::MouseButtonRealeased, EventCategory::EventCategoryMouseButton | EventCategory::EventCategoryInput),
				m_button(button) {}
			static EventType getStaticType() { return EventType::MouseButtonRealeased; }
			virtual EventType getEventType() const override { return EventType::MouseButtonRealeased; }
			virtual int32_t getCategoryFlags() const override { return EventCategoryMouseButton; }
			uint32_t getButton() { return m_button; }
		protected:
			uint32_t m_button;
	};

	/** \class MouseMovedEvent */

	class MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(int32_t newXPos, int32_t newYPos) : Event(EventType::MouseMoved, EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput),
			m_newXPos(newXPos), m_newYPos(newYPos) {}
		static EventType getStaticType() { return EventType::MouseMoved; }
		virtual EventType getEventType() const override { return EventType::MouseMoved; }
		virtual int32_t getCategoryFlags() const override { return EventCategoryMouse; }
		int32_t getNewXPos() { return m_newXPos; }
		int32_t getNewYPos() { return m_newYPos; }
	protected:
		int32_t m_newXPos;
		int32_t m_newYPos;
	};

	/** \class MouseScrolledEvent */

	class MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent(int32_t offset) : Event(EventType::MouseScrolled, EventCategory::EventCategoryMouse | EventCategory::EventCategoryInput),
			m_offset(offset) {}
		static EventType getStaticType() { return EventType::MouseScrolled; }
		virtual EventType getEventType() const override { return EventType::MouseScrolled; }
		virtual int32_t getCategoryFlags() const override { return EventCategoryMouse; }
		int32_t getOffset() { return m_offset; }
	protected:
		int32_t m_offset;
	};

}
