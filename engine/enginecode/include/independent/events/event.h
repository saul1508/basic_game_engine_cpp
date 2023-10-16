/** \file event.h */
#pragma once
#include <spdlog/spdlog.h>


enum class EventType {
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLoseFocus, WindowMove,
	KeyPress, KeyRealease, KeyType,
	MouseButtonPress, MouseButtonRealease, MouseMove, MouseScroll
};

enum EventCategory {
	None = 0,
	EventCategoryWindow = 1 << 0, //00000001
	EventCategoryInput = 1 << 1, //00000010
	EventCategoryKeyboard = 1 << 2, //00000100
	EventCategoryMouse = 1 << 3, //00001000
	EventCategoryMouseButton = 1 << 4 //00010000
};

/** \class Event
* An abstract base class for the event handling system
*/

class Event {
	public:
		Event() {}; //!< Default constructor
		Event(EventType type, int32_t categoryFlags) : m_eventType(type), m_categoryFlags(categoryFlags) {}
		virtual EventType getEventType() const { return m_eventType; }	//!< Gets the event type
		virtual int32_t getCategoryFlags() const { return m_categoryFlags; } //!< Gets the event category
		inline bool handled() const { return m_handled; } //!< Checks whether event has been handled
		inline void handle(bool isHandled) { m_handled = isHandled; } //!< Handled the event
		inline bool isCategory(EventCategory category) { return getCategoryFlags() & category; } //!< Returns wether the event is in a specified category
	protected:
		EventType m_eventType = EventType::None; //!< Stores type of event
		int32_t m_categoryFlags = EventCategory::None; //!< Stores event category as category flags
		bool m_handled = false; //!< Attribute to denote whether an event has been handled or not
};

