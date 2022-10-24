#pragma once
#include <QtWidgets>

#include "InstrumentEnum.h"

class ProgramState : public QObject {
	Q_OBJECT
private:
	ProgramState() {}
	void _setMode(InstrumentEnum mode) {
		this->mode = mode;
		emit changedMode();
	}
public:
	static void init() {
		instance = new ProgramState;
	}
	static ProgramState* getInstance() { return instance; }

	static void setMode(InstrumentEnum mode) {
		instance->_setMode(mode);
	}
	
	static InstrumentEnum getMode() { return instance->mode; }

signals:
	void changedMode();
private:
	InstrumentEnum mode = InstrumentEnum::DEFAULT;

	static inline ProgramState* instance = nullptr;
};
