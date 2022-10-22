#include "PanelOfInstruments.h"

PanelOfInstruments::PanelOfInstruments(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	auto paintButton = new QPushButton("Paint", this);
	connect(paintButton, &QPushButton::clicked, MainWindow::getInstance()->getShowedImage(), &ImageWidget::paintModeChange);
	layout->addWidget(paintButton, 0, Qt::AlignTop);
}

PanelOfInstruments::~PanelOfInstruments()
{}
