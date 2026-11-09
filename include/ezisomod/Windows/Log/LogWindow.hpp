#ifndef LOG_LOGWINDOW_HPP
#define LOG_LOGWINDOW_HPP
// Includes
#include <QFileDialog>
#include <QMessageBox>
#include <QScrollBar>
#include <QTimer>
#include <QWidget>
#include <ezisomod/Log/Logger.hpp>

// Namespaces
QT_BEGIN_NAMESPACE
namespace Ui {
	class LogWindow;
}
QT_END_NAMESPACE

namespace Windows {
	/// Classes
	class LogWindow: public QWidget {
		Q_OBJECT
		public:
			//// Constructor / Destructor
			LogWindow(Log::Logger *RuntimeLog, QWidget *Parent = nullptr);
			~LogWindow();

		private:
			//// Variables
			Log::LogEventTypes CurrentFilter = Log::LogEventTypes::PLEASEGETALLEVENTSBUTDEBUG;
			Log::Logger *RuntimeLog;
			QTimer *LogUpdater;
			Ui::LogWindow *ui;

			//// Functions
			void ReloadLogs();
			void SaveLogsInMemory();
			void SetFilterByIndex(int Index);
			void SetUpFilterComboBox();
			void ShowCriticalMessage(QString Title, QString Text);
			void ShowInfoMessage(QString Title, QString Text);
	};
}

#endif // LOG_LOGWINDOW_HPP
