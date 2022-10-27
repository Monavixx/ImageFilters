#include "PanelOfParametersOfCurrentInstrument.h"


PanelOfParametersOfCurrentInstrument::PanelOfParametersOfCurrentInstrument(QWidget* parent) {
	connect(ProgramState::getInstance(), &ProgramState::changedMode, this, &PanelOfParametersOfCurrentInstrument::changedMode);

	defaultParameters = new QWidget(this);

	//paint
	paintParameters = new QWidget(this);
	QVBoxLayout* paintVlayout = new QVBoxLayout(paintParameters);

	QLabel* paintLabelWidth = new QLabel("Width:", paintParameters);
	QSpinBox* paintSpinboxWidth = new QSpinBox(paintParameters);
	connect(paintSpinboxWidth, &QSpinBox::valueChanged, [](int value) {
		MainWindow::getInstance()->getShowedImage()->getPaintManager().setWidth(value);
	});
	QHBoxLayout* paintWidthHlayout = new QHBoxLayout(paintParameters);
	paintWidthHlayout->addWidget(paintLabelWidth);
	paintWidthHlayout->addWidget(paintSpinboxWidth);
	paintVlayout->addLayout(paintWidthHlayout);

	QLabel* paintLabelColor = new QLabel("Color:", paintParameters);
	QPushButton* paintButtonColor = new QPushButton("Choose", paintParameters);
	connect(paintButtonColor, &QPushButton::clicked, []() {
		MainWindow::getInstance()->getShowedImage()->getPaintManager().setColor(QColorDialog::getColor());
	});
	QHBoxLayout* paintColorHlayout = new QHBoxLayout(paintParameters);
	paintColorHlayout->addWidget(paintLabelColor);
	paintColorHlayout->addWidget(paintButtonColor);
	paintVlayout->addLayout(paintColorHlayout);

	hideAll();
	defaultParameters->show();
	setMinimumSize(paintParameters->size());
}
PanelOfParametersOfCurrentInstrument::~PanelOfParametersOfCurrentInstrument() {

}

void PanelOfParametersOfCurrentInstrument::hideAll() {
	paintParameters->hide();
	defaultParameters->hide();
}

void PanelOfParametersOfCurrentInstrument::changedMode() {
	hideAll();
	switch (ProgramState::getMode())
	{
	case InstrumentEnum::PAINT: {
		paintParameters->show();
		break;
	}
	case InstrumentEnum::DEFAULT: {
		defaultParameters->show();
		break;
	}
	}
}
