// Includes
#include <ezisomod/Log/Logger.hpp>

// Namespaces
namespace Log {
	/// Constructor / Destructor
	Logger::Logger(QString DataPath) {
		LogFilePath = DataPath + "Logs/log-" + QDateTime::currentDateTime().toString("MMddyyyy'-'hhmmss") + ".txt";

		QDir *LogDir = new QDir(DataPath + "Logs/");
		if(!LogDir->exists())
			LogDir->mkpath(DataPath + "Logs/");

		delete LogDir;

		LogEvent(LogEventTypes::LOG_INFO, "ezisomod started!");
	}

	Logger::~Logger() {
		LogEvent(LogEventTypes::LOG_INFO, "Closing ezisomod! Goodbye!", false);
	}

	/// Functions
	QString Logger::GetAllEventsAsString(LogEventTypes TypeFilter) {
		QString FilteredEvents;

		for(auto &CurrentLogEvent : LogEvents) {
			if(TypeFilter == LogEventTypes::PLEASEGETALLEVENTS || ((TypeFilter == LogEventTypes::PLEASEGETALLEVENTSBUTDEBUG && CurrentLogEvent.GetEventType() != LogEventTypes::LOG_DEBUG) || CurrentLogEvent.GetEventType() == TypeFilter))
				FilteredEvents += CurrentLogEvent.GetString();
		}

		return FilteredEvents;
	}

	void Logger::LogEvent(LogEventTypes EventType, QString Data, bool AddNewLine) {
		if(LogEvents.size() + 1 > MaximumEventsInMemoryAllowed)
			LogEvents.pop_front();

		QString RealData = Data;
		//// Always end with at least one new line! Unix is my best friend!
		RealData += "\n";
		if(AddNewLine)
			RealData += "\n";

		BasicLogEvent CurrentEvent(EventType, RealData);
		LogEvents.push_back(CurrentEvent);

		if(RealFileAvailable) {
			QFile *RawLogFile = new QFile(LogFilePath);

			if(!RawLogFile->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)) {
				RealFileAvailable = false;
				qWarning() << "WARNING!!! Raw log file at " << LogFilePath << " is UNOPENABLE! Any logs output past this warning will NOT be automatically saved to a real file this session! Open the log window to manually save a file!";
			} else {
				QTextStream LogStream(RawLogFile);
				LogStream << CurrentEvent.GetString();

				RawLogFile->close();
			}

			delete RawLogFile;
		}
	}

	void Logger::SetMaximumEventsAllowedInMemory(int NewLimit) {
		MaximumEventsInMemoryAllowed = NewLimit;
	}
}
