// Includes
#include <ezisomod/Windows/MainWindow.hpp>
#include "./ui_MainWindow.h"

// Namespaces
namespace Windows {
	/// Constructor / Destructor
	MainWindow::MainWindow(QWidget *Parent): QMainWindow(Parent), ui(new Ui::MainWindow) {
		ui->setupUi(this);

		RuntimeLog = new Log::Logger(QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "/fryelum/ezisomod/");
		Log = new LogWindow(RuntimeLog);
		About = new AboutWindow();

		SetUpButtons();
	}

	MainWindow::~MainWindow() {
		delete ui;
	}

	/// Functions
	void MainWindow::OpenAboutWindow() {
		About->show();
	}

	void MainWindow::OpenLogWindow() {
		Log->show();
	}

	void MainWindow::OpenSourceISOFile() {
		QString OpenISOPath;
		QFile ISOFile;

		OpenISOPath = QFileDialog::getOpenFileName(this, tr("Open an ISO file!"), "", tr("ISO files (*.ISO, *.iso);;All Files (*)"));
		if(OpenISOPath.isEmpty() || OpenISOPath.isNull()) {
			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_WARNING, "FAILED to open a source ISO file with reason: no file chosen.");
			ShowCriticalMessage("Error opening file!", "Please choose a file!");

			return;
		}

		ISOFile.setFileName(OpenISOPath);
		if(!ISOFile.open(QIODevice::ReadWrite)) {
			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("FAILED to open file %1 with reason: %2").arg(OpenISOPath).arg(ISOFile.errorString()));
			ShowCriticalMessage("Failed to open file! Try again...", QString("Maybe check permissions? Error: %1").arg(ISOFile.errorString()));

			return;
		}

		if(ui->ModeTabs->currentIndex() == 0)
			//// Inject a File!
			ui->InjectSourceISOLineEdit->setText(ISOFile.fileName());
		else {
			//// Extract a File!
			ui->ExtractSourceISOLineEdit->setText(ISOFile.fileName());
		}

		ISOFile.close();
	}

	void MainWindow::OpenSourceOrExtractFile() {
		QString OpenFilePath;
		QFile OpenFile;

		if(ui->ModeTabs->currentIndex() == 0) {
			//// Inject a File!
			OpenFilePath = QFileDialog::getOpenFileName(this, tr("Open a source file!"), "", tr("All Files (*)"));
			if(OpenFilePath.isEmpty() || OpenFilePath.isEmpty()) {
				RuntimeLog->LogEvent(Log::LogEventTypes::LOG_WARNING, "FAILED to open a source file with reason: no file chosen.");
				ShowCriticalMessage("Error opening file!", "Please choose a file!");

				return;
			}
		} else {
			//// Extract a File!
			OpenFilePath = QFileDialog::getSaveFileName(this, tr("Open a file to extract to!"), "", tr("All Files (*)"));
			if(OpenFilePath.isEmpty() || OpenFilePath.isEmpty()) {
				RuntimeLog->LogEvent(Log::LogEventTypes::LOG_WARNING, "FAILED to open a file to extract to with reason: no file chosen.");
				ShowCriticalMessage("Error opening file!", "Please choose a file!");

				return;
			}
		}

		OpenFile.setFileName(OpenFilePath);
		if(!OpenFile.open(QIODevice::ReadWrite)) {
			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("FAILED to open file %1 with reason: %2").arg(OpenFilePath).arg(OpenFile.errorString()));
			ShowCriticalMessage("Failed to open file! Try again...", QString("Maybe check permissions? Error: %1").arg(OpenFile.errorString()));

			return;
		}

		if(ui->ModeTabs->currentIndex() == 0)
			//// Inject a File!
			ui->InjectSourceFileLineEdit->setText(OpenFile.fileName());
		else {
			//// Extract a File!
			ui->ExtractOutputFileLineEdit->setText(OpenFile.fileName());
		}

		OpenFile.close();
	}

	void MainWindow::RunTheTool() {
		if(ui->ModeTabs->currentIndex() == 0) {
			if((ui->InjectSourceFileLineEdit->text().isEmpty() || ui->InjectSourceFileLineEdit->text().isNull()) ||
			(ui->InjectSourceISOLineEdit->text().isEmpty() || ui->InjectSourceISOLineEdit->text().isNull()) ||
			(ui->InjectTargetPathLineEdit->text().isEmpty() || ui->InjectTargetPathLineEdit->text().isNull())) {
				RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, "FAILED to run isomod! One of the inputs were empty or null. Ensure everything looks right!");
				ShowCriticalMessage("Failed to run isomod!", "Ensure every box is filled and looks right!");

				return;
			}

			libisomod::putFile(ui->InjectSourceISOLineEdit->text().toStdString(), ui->InjectTargetPathLineEdit->text().toStdString(), ui->InjectSourceFileLineEdit->text().toStdString());
		} else {
			if((ui->ExtractSourceISOLineEdit->text().isEmpty() || ui->ExtractSourceISOLineEdit->text().isNull()) ||
			(ui->ExtractOutputFileLineEdit->text().isEmpty() || ui->ExtractOutputFileLineEdit->text().isNull()) ||
			(ui->ExtractTargetPathLineEdit->text().isEmpty() || ui->ExtractTargetPathLineEdit->text().isNull())) {
				RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, "FAILED to run isomod! One of the inputs were empty or null. Ensure everything looks right!");
				ShowCriticalMessage("Failed to run isomod!", "Ensure every box is filled and looks right!");

				return;
			}

			libisomod::getFile(ui->ExtractSourceISOLineEdit->text().toStdString(), ui->ExtractTargetPathLineEdit->text().toStdString(), ui->ExtractOutputFileLineEdit->text().toStdString());
		}

		if(libisomod::statusCode != 0) {
			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, "FAILED to run isomod! Look at the following output for an error and what happened:");
			RuntimeLog->LogEvent(Log::LogEventTypes::LOG_ERROR, QString("isomod error: %1").arg(libisomod::isomodError));

			ShowCriticalMessage("Failed to run isomod!", "Check the log for specific details.");
		} else {
			ShowInfoMessage("Success!", "Ran isomod successfully! Check the log for more specific details.");
		}

		RuntimeLog->LogEvent(Log::LogEventTypes::LOG_INFO, QString("isomod output:\n%1").arg(libisomod::isomodOutput.str()));
	}

	void MainWindow::SetUpButtons() {
		//// Menubar
		connect(ui->MenubarActionAbout, &QAction::triggered, this, &MainWindow::OpenAboutWindow);
		connect(ui->MenubarActionOpenLogWindow, &QAction::triggered, this, &MainWindow::OpenLogWindow);
		connect(ui->MenubarActionQuit, &QAction::triggered, this, &MainWindow::close);

		//// Functionality
		connect(ui->ExtractExtractButton, &QPushButton::clicked, this, &MainWindow::RunTheTool);
		connect(ui->ExtractOutputFileBrowseButton, &QPushButton::clicked, this, &MainWindow::OpenSourceOrExtractFile);
		connect(ui->ExtractSourceISOBrowseButton, &QPushButton::clicked, this, &MainWindow::OpenSourceISOFile);
		connect(ui->InjectInjectButton, &QPushButton::clicked, this, &MainWindow::RunTheTool);
		connect(ui->InjectSourceFileBrowseButton, &QPushButton::clicked, this, &MainWindow::OpenSourceOrExtractFile);
		connect(ui->InjectSourceISOBrowseButton, &QPushButton::clicked, this, &MainWindow::OpenSourceISOFile);
	}

	void MainWindow::ShowCriticalMessage(QString Title, QString Text) {
		QMessageBox CriticalMessage;
		CriticalMessage.critical(0, Title, Text);
	}

	void MainWindow::ShowInfoMessage(QString Title, QString Text) {
		QMessageBox InfoMessage;
		InfoMessage.information(0, Title, Text);
	}

	void MainWindow::closeEvent(QCloseEvent *Event) {
		Log->close();
		delete Log;
		delete RuntimeLog;

		About->close();
		delete About;
	}
}
