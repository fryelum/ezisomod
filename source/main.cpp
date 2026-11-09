// Includes
#include <QApplication>
#include <ezisomod/Windows/MainWindow.hpp>

// Functions
int main(int argc, char *argv[]) {
	QApplication MainApplication(argc, argv);

	Windows::MainWindow ezisomodWindow;
	ezisomodWindow.show();

	return MainApplication.exec();
}
