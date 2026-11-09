#ifndef LOG_BASICLOGEVENT_HPP
#define LOG_BASICLOGEVENT_HPP
// Includes
#include <QDateTime>
#include <QStandardPaths>
#include <QString>

// Namespaces
namespace Log {
	/// Enums
	enum LogEventTypes {
		LOG_ERROR,
		LOG_DEBUG,
		LOG_INFO,
		LOG_WARNING,
		PLEASEGETALLEVENTS,
		PLEASEGETALLEVENTSBUTDEBUG
	};

	/// Log Levels
	static const char *LogEventTypesChar[] = {
		"LOG_ERROR",
		"LOG_DEBUG",
		"LOG_INFO",
		"LOG_WARNING"
	};

	/// Classes
	class BasicLogEvent {
		public:
			//// Constructor
			BasicLogEvent(LogEventTypes EventType, QString Data);

			//// Functions
			LogEventTypes GetEventType();
			QString GetString();

		private:
			//// Variables
			LogEventTypes EventType;
			QDateTime TimeOfEvent;
			QString Data;
	};
}

#endif // LOG_BASICLOGEVENT_HPP
