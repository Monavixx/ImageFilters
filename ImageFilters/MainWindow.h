#pragma once
#include <thread>

#include <QtWidgets>

#include "filters/NegativeFilter.h"
#include "filters/CircleDarkerFilter.h"
#include "ImageWidget.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void fileOpenImageSlot();
	void fileSaveImageSlot();
	void fileCreateNewImageSlot();
	void filtersNegativeSlot();
	void filtersCirleDarkerSlot();
	
private:
	ImageWidget* showedImage;
	

	QImage curImage;

	void updateImage();
	void updateImage(const QImage& image);
};
