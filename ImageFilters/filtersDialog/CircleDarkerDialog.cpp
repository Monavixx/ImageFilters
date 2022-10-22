#include "CircleDarkerDialog.h"

CircleDarkerDialog::CircleDarkerDialog(QWidget* parent): QDialog(parent) {
	MainWindow* mainWindow = MainWindow::getInstance();
	this->setWindowTitle("Input radius");
	QSlider* slider = new QSlider(Qt::Horizontal, this);
	slider->setRange(0,
		mainWindow->curImage().width() > mainWindow->curImage().height()
		? mainWindow->curImage().width() : mainWindow->curImage().height());
	slider->setPageStep(1);

	slider->setValue(100);

	QPushButton* pbExit = new QPushButton("apply", this);
	QVBoxLayout* vlayout = new QVBoxLayout(this);
	vlayout->addWidget(slider);
	vlayout->addWidget(pbExit);

	QImage* oldImage = new QImage(mainWindow->curImage());
	connect(slider, &QSlider::valueChanged, [mainWindow, oldImage](int value) {
		mainWindow->updateImage(CircleDarkerFilter(value).filter(*oldImage));
	});
	connect(pbExit, &QPushButton::clicked, [this, slider, mainWindow, oldImage]() {
		mainWindow->updateImage(CircleDarkerFilter(slider->value()).filter(*oldImage));
		this->close();
		delete oldImage;
	});
}