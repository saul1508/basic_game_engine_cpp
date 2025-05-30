/** \file event.h */
#pragma once
#include <spdlog/spdlog.h>


enum class EventType { //!< Enum storing all event types
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLoseFocus, WindowMove,
	KeyPress, KeyRealease, KeyType,
	MouseButtonPress, MouseButtonRealease, MouseMove, MouseScroll
};

enum EventCategory { //!< Enum storing event category flags
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
		Event(EventType type, int32_t categoryFlags) : m_eventType(type), m_categoryFlags(categoryFlags) {} //!< Constuctor
		EventType getEventType() const { return m_eventType; }	//!< Getter method for event type
		int32_t getCategoryFlags() const { return m_categoryFlags; } //!< Getter methof got event category
		inline bool handled() const { return m_handled; } //!< Method to check whether event has been handled
		inline void handle(bool isHandled) { m_handled = isHandled; } //!< Method to handle the event
		inline bool isCategory(EventCategory category) const { return getCategoryFlags() & category; } //!< Method to get the category of an event
	protected:
		EventType m_eventType = EventType::None; //!< Attribute for the type of event
		int32_t m_categoryFlags = EventCategory::None; //!< Atrribute for the category of the event as category flags
		bool m_handled = false; //!< Attribute to denote whether an event has been handled or not
};

