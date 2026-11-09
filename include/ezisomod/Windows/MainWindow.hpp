#ifndef WINDOWS_MAINWINDOW_HPP
#define WINDOWS_MAINWINDOW_HPP
// Includes
#include <QMainWindow>
#include <QStandardPaths>
#include <ezisomod/Windows/About/AboutWindow.hpp>
#include <ezisomod/Windows/Log/LogWindow.hpp>
#include <pwf2tools/libisomod.h>

// Namespaces
QT_BEGIN_NAMESPACE
namespace Ui {
	class MainWindow;
}
QT_END_NAMESPACE

namespace Windows {
	/// Classes
	class MainWindow: public QMainWindow {
		Q_OBJECT
		public:
			//// Constructor / Destructor
			MainWindow(QWidget *Parent = nullptr);
			~MainWindow();

		private slots:
			//// Functions
			void closeEvent(QCloseEvent *Event);

		private:
			//// Variables
			AboutWindow *About;
			LogWindow *Log;
			Log::Logger *RuntimeLog;
			Ui::MainWindow *ui;

			//// Functions
			void OpenAboutWindow();
			void OpenLogWindow();
			void OpenSourceISOFile();
			void OpenSourceOrExtractFile();
			void RunTheTool();
			void SetUpButtons();
			void ShowCriticalMessage(QString Title, QString Text);
			void ShowInfoMessage(QString Title, QString Text);
	};
}

#endif // WINDOWS_MAINWINDOW_HPP
