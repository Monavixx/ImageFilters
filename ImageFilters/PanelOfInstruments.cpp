#include "PanelOfInstruments.h"

PanelOfInstruments::PanelOfInstruments(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	auto viewButton = new QPushButton("View", this);
	connect(viewButton, &QPushButton::clicked, []() {ProgramState::setMode(InstrumentEnum::DEFAULT); });
	layout->addWidget(viewButton, 0, Qt::AlignTop);
	auto paintButton = new QPushButton("Paint", this);
	connect(paintButton, &QPushButton::clicked, []() {ProgramState::setMode(InstrumentEnum::PAINT); });
	layout->addWidget(paintButton, 0, Qt::AlignTop);

}

PanelOfInstruments::~PanelOfInstruments()
{}
