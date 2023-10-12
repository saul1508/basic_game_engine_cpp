/** \file eventDispatcher.h */
#pragma once
#include "event.h"

/** \class EventDispacher */
class EventDispatcher {
	template<typename T>
	using EventFunc = std::function<bool(T&)>; //!< Sets EventFunc to a function which returns a boolean and takes reference to a class which meets templace type T
	public:
		EventDispatcher(Event& event) : m_event(event) { } //!< Constuctor setting m_event
		template<typename T>
		bool dispatch(EventFunc<T> func) { //!< Dispatch function taking an EventFunc as a parameter
			if (m_event.getEventType() == T::getStaticType()) { //!< Checks if te event type is the right one to dispatch
				m_event.handle(func(*((T*)&m_event))); //!< Handles the function
				return true;
			}
			return false; 
		}
	protected:
		Event& m_event; //!< Abstract reference to an event
};
