#ifndef ABOUT_ABOUTWINDOW_HPP
#define ABOUT_ABOUTWINDOW_HPP
// Includes
#include <QDate>
#include <QDialog>
#include <QLabel>
#include <QObject>
#include <QPixmap>
#include <ezisomod/About/Info.hpp>

// Namespaces
QT_BEGIN_NAMESPACE
namespace Ui {
    class AboutWindow;
}
QT_END_NAMESPACE

namespace Windows {
	/// Classes
	class AboutWindow: public QDialog {
		Q_OBJECT
		public:
			//// Constructor / Destructor
			AboutWindow(QWidget *parent = nullptr);
			~AboutWindow();

		private slots:
			//// Functions
			void LeaveWindow();

		private:
			//// Variables
			Ui::AboutWindow *ui;
	};
}

#endif // ABOUT_ABOUTWINDOW_HPP
