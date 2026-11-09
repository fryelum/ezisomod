// Includes
#include <ezisomod/Windows/Log/LogWindow.hpp>
#include "./ui_LogWindow.h"

// Namespaces
namespace Windows {
	/// Constructor / Destructor
	LogWindow::LogWindow(Log::Logger *RuntimeLog, QWidget *Parent): QWidget(Parent), ui(new Ui::LogWindow) {
		ui->setupUi(this);

		this->RuntimeLog = RuntimeLog;
		connect(ui->LogTypeFilterComboBox, &QComboBox::currentIndexChanged, this, &LogWindow::SetFilterByIndex);

		SetUpFilterComboBox();

		connect(ui->CloseButton, &QPushButton::pressed, this, [&]() { close(); });
		connect(ui->SaveButton, &QPushButton::pressed, this, [&]() { SaveLogsInMemory(); });

		LogUpdater = new QTimer(this);
		connect(LogUpdater, &QTimer::timeout, this, &LogWindow::ReloadLogs);
		LogUpdater->start(1000);
	}

	LogWindow::~LogWindow() {
		delete ui;
	}

	/// Functions
	void LogWindow::ReloadLogs() {
		if(!this->isVisible())
			return;

		QString *TempText = new QString(RuntimeLog->GetAllEventsAsString(CurrentFilter));
		if(ui->LogTextEdit->toPlainText() == *TempText) {
			delete TempText;
			
			return;
		}

		int CurrentScrollBarPosition = ui->LogTextEdit->verticalScrollBar()->value();
		ui->LogTextEdit->setText(*TempText);
		ui->LogTextEdit->verticalScrollBar()->setValue(CurrentScrollBarPosition);

		delete TempText;
	}

	void LogWindow::SaveLogsInMemory() {
		QString LogFilePath;
		QFile LogFile;

		LogFilePath = QFileDialog::getSaveFileName(this, tr("Open a log file to save to!"), "", tr("Log File (*.log);;All Files (*)"));
		if(LogFilePath.isEmpty() || LogFilePath.isNull()) {
			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, "FAILED to open a live log file to save to with reason: no file chosen.");
			ShowCriticalMessage("Error opening file!", "Please choose a file!");

			return;
		}

		LogFile.setFileName(LogFilePath);
		if(!LogFile.open(QIODevice::ReadWrite)) {
			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("FAILED to open file %1 with reason: %2").arg(LogFilePath).arg(LogFile.errorString()));
			ShowCriticalMessage("Failed to open file! Try again...", QString("Maybe check permissions? Error: %1").arg(LogFile.errorString()));

			return;
		}

		QTextStream LogStream(&LogFile);
		LogStream << RuntimeLog->GetAllEventsAsString(Log::LogEventTypes::PLEASEGETALLEVENTS);

		LogFile.close();

		ShowInfoMessage("Success!", QString("Successfully saved live log to %1.").arg(LogFilePath));
	}

	void LogWindow::SetFilterByIndex(int Index) {
		CurrentFilter = static_cast<Log::LogEventTypes>(ui->LogTypeFilterComboBox->itemData(Index).toInt());

		ReloadLogs();
	}

	void LogWindow::SetUpFilterComboBox() {
		ui->LogTypeFilterComboBox->addItem("All Events (No Debug)", Log::LogEventTypes::PLEASEGETALLEVENTSBUTDEBUG);
		ui->LogTypeFilterComboBox->addItem("All Events", Log::LogEventTypes::PLEASEGETALLEVENTS);
		ui->LogTypeFilterComboBox->addItem("Debug", Log::LogEventTypes::LOG_DEBUG);
		ui->LogTypeFilterComboBox->addItem("Errors", Log::LogEventTypes::LOG_ERROR);
		ui->LogTypeFilterComboBox->addItem("Information", Log::LogEventTypes::LOG_INFO);
		ui->LogTypeFilterComboBox->addItem("Warnings", Log::LogEventTypes::LOG_WARNING);

		ui->LogTypeFilterComboBox->setCurrentIndex(0);
	}

	void LogWindow::ShowCriticalMessage(QString Title, QString Text) {
		QMessageBox CriticalMessage;
		CriticalMessage.critical(0, Title, Text);
	}

	void LogWindow::ShowInfoMessage(QString Title, QString Text) {
		QMessageBox InfoMessage;
		InfoMessage.information(0, Title, Text);
	}
}
