#pragma once
#include <QtWidgets>
#include "ProgramState.h"

class PanelOfParametersOfCurrentInstrument : public QWidget {
	Q_OBJECT

public:
	PanelOfParametersOfCurrentInstrument(QWidget* parent = nullptr);
	~PanelOfParametersOfCurrentInstrument();

	void hideAll();

public slots:
	void changedMode();

private:
	QWidget* defaultParameters;
	QWidget* paintParameters;
};
