#include <QtWidgets>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	CircleDarkerFilter::init();

	MainWindow* mw = MainWindow::getInstance();
	mw->init();
	mw->showMaximized();

	int code = app.exec();
	delete mw;
	return code;
}
