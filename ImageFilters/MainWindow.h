#pragma once
#include <QtWidgets>

#include "filters/NegativeFilter.h"
#include "filters/CircleDarkerFilter.h"
#include "filtersDialog/CircleDarkerDialog.h"
#include "ImageWidget.h"
#include "PanelOfInstruments.h"
#include "PanelOfParametersOfCurrentInstrument.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	void init();
	~MainWindow();
	static MainWindow* getInstance() {
		if (instance == nullptr) {
			instance = new MainWindow();
		}
		return instance;
	}
	QImage& curImage() {
		return showedImage->getImage();
	}
	void setCurImage(const QImage& newImage) {
		showedImage->setImage(newImage);
	}
	void updateImage();
	void updateImage(const QImage& image);

	ImageWidget* getShowedImage() {
		return showedImage;
	}

public slots:

private slots:
	void fileOpenImageSlot();
	void fileSaveImageSlot();
	void fileCreateNewImageSlot();
	void filtersNegativeSlot();
	void filtersCirleDarkerSlot();
	
private:
	static inline MainWindow* instance;

	ImageWidget* showedImage;
	class PanelOfInstruments* panelOfInstruments;
	class PanelOfParametersOfCurrentInstrument* panelOfParametersOfCurrentInstrument;

	
};
