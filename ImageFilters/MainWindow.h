#pragma once
#include <thread>

#include <QtWidgets>

#include "filters/NegativeFilter.h"
#include "filters/CircleDarkerFilter.h"
#include "filtersDialog/CircleDarkerDialog.h"
#include "ImageWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	static MainWindow* getInstance() {
		if (instance == nullptr) {
			instance = new MainWindow();
		}
		return instance;
	}
	QImage& getCurImage() { return curImage; }
	void setCurImage(const QImage& newImage) { curImage = newImage; }
	void updateImage();
	void updateImage(const QImage& image);

private slots:
	void fileOpenImageSlot();
	void fileSaveImageSlot();
	void fileCreateNewImageSlot();
	void filtersNegativeSlot();
	void filtersCirleDarkerSlot();
	
private:
	static inline MainWindow* instance;

	ImageWidget* showedImage;
	
	QImage curImage;
};
