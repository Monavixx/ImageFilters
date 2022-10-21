#include "CircleDarkerDialog.h"

CircleDarkerDialog::CircleDarkerDialog(QWidget* parent): QDialog(parent) {
	MainWindow* mainWindow = MainWindow::getInstance();
	this->setWindowTitle("Input radius");
	QSlider* slider = new QSlider(Qt::Horizontal, this);
	slider->setRange(0,
		mainWindow->getCurImage().width() > mainWindow->getCurImage().height()
		? mainWindow->getCurImage().width() : mainWindow->getCurImage().height());
	slider->setPageStep(1);

	slider->setValue(100);

	QPushButton* pbExit = new QPushButton("apply", this);
	QVBoxLayout* vlayout = new QVBoxLayout(this);
	vlayout->addWidget(slider);
	vlayout->addWidget(pbExit);
	connect(slider, &QSlider::valueChanged, [mainWindow](int value) {
		mainWindow->updateImage(CircleDarkerFilter(value).filter(mainWindow->getCurImage()));
	});
	connect(pbExit, &QPushButton::clicked, [this, slider, mainWindow]() {
		mainWindow->setCurImage(CircleDarkerFilter(slider->value()).filter(mainWindow->getCurImage()));
		mainWindow->updateImage();
		this->close();
	});
}