// Includes
#include <ezisomod/Log/BasicLogEvent.hpp>

// Namespaces
namespace Log {
	/// Constructor
	BasicLogEvent::BasicLogEvent(LogEventTypes EventType, QString Data) {
		this->EventType = EventType;
		this->Data = Data;
		TimeOfEvent = QDateTime::currentDateTime();
	}

	/// Functions
	LogEventTypes BasicLogEvent::GetEventType() {
		return EventType;
	}

	QString BasicLogEvent::GetString() {
		return "[" + TimeOfEvent.toString("dddd, MMMM dd, yyyy '-' hh:mm:ss") + ", " + LogEventTypesChar[EventType] + "] - "+ Data;
	}
}
