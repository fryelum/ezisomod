// Includes
#include <ezisomod/Windows/About/AboutWindow.hpp>
#include "./ui_AboutWindow.h"

// Namespaces
namespace Windows {
	/// Constructor / Destructor
	AboutWindow::AboutWindow(QWidget *parent): QDialog(parent), ui(new Ui::AboutWindow) {
		ui->setupUi(this);

		QPixmap Icon(":/img/pwf2tools-scaled.png");
		ui->AppIcon->setPixmap(Icon.scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));

		QObject::connect(ui->OKButton, SIGNAL(clicked()), this, SLOT(LeaveWindow()));
		ui->VersionLabel->setText(QString("Version %1.%2.%3").arg(MAJOR_VERSION).arg(MINOR_VERSION).arg(PATCH_VERSION));
		ui->BuiltOnDateLabel->setText("Built on " + QDate::fromString(QString(__DATE__).simplified(), "MMM d yyyy").toString("MMM dd, yyyy") + " at " + QString::fromStdString(__TIME__));
	}

	AboutWindow::~AboutWindow() {
		delete ui;
	}

	/// Functions
	void AboutWindow::LeaveWindow() {
		AboutWindow::close();
	}
}
