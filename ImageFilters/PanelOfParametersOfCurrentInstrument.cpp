#include "PanelOfParametersOfCurrentInstrument.h"


PanelOfParametersOfCurrentInstrument::PanelOfParametersOfCurrentInstrument(QWidget* parent) {
	connect(ProgramState::getInstance(), &ProgramState::changedMode, this, &PanelOfParametersOfCurrentInstrument::changedMode);

	paintParameters = new QWidget(this);
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
