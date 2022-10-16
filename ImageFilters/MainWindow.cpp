#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	//menu
	QMenu* fileMenu = menuBar()->addMenu("File");
	QAction* fileOpenImageAction = fileMenu->addAction("Open image", QKeySequence::Open);
	connect(fileOpenImageAction, &QAction::triggered, this, &MainWindow::fileOpenImageSlot);
	QAction* fileSaveImageAction = fileMenu->addAction("Save image", QKeySequence::Save);
	connect(fileSaveImageAction, &QAction::triggered, this, &MainWindow::fileSaveImageSlot);
	QAction* fileCreateNewImageAction = fileMenu->addAction("Create new image", QKeySequence::New);
	connect(fileCreateNewImageAction, &QAction::triggered, this, &MainWindow::fileCreateNewImageSlot);

	QMenu* filtersMenu = menuBar()->addMenu("Filters");
	QAction* filterNegativeAction = filtersMenu->addAction("Negative");
	connect(filterNegativeAction, &QAction::triggered, this, &MainWindow::filtersNegativeSlot);
	QAction* filterSecondAction = filtersMenu->addAction("Circle darker");
	connect(filterSecondAction, &QAction::triggered, this, &MainWindow::filtersCirleDarkerSlot);

	// Image
	showedImage = new ImageWidget(this);
	setCentralWidget(showedImage);
}

MainWindow::~MainWindow()
{}

void MainWindow::updateImage()
{
	showedImage->setPixmap(QPixmap::fromImage(curImage));
}
void MainWindow::updateImage(const QImage& image) {
	showedImage->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::fileOpenImageSlot() {
	QString filename{ QFileDialog::getOpenFileName(this, "Open image", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation), "*.png")};
	curImage.load(filename);

	updateImage();
}

void MainWindow::fileSaveImageSlot() {
	curImage.save(QFileDialog::getSaveFileName(this, "Save image", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation), "*.png"));
}

void MainWindow::filtersNegativeSlot() {
	curImage = NegativeFilter().filter(curImage);
	updateImage();
}

void MainWindow::filtersCirleDarkerSlot() {
	QDialog* dialog = new QDialog(this);
	dialog->setWindowTitle("Input radius");
	QSlider* slider = new QSlider(Qt::Horizontal, dialog);
	slider->setRange(0, curImage.width() > curImage.height() ? curImage.width() : curImage.height());
	slider->setPageStep(1);

	slider->setValue(100);

	QPushButton* pbExit = new QPushButton("apply", dialog);
	QVBoxLayout* vlayout = new QVBoxLayout(dialog);
	vlayout->addWidget(slider);
	vlayout->addWidget(pbExit);
	connect(slider, &QSlider::valueChanged, [this](int value) {
		updateImage(CircleDarkerFilter(value).filter(curImage));
	});
	connect(pbExit, &QPushButton::clicked, [dialog, slider, this]() {
		curImage = CircleDarkerFilter(slider->value()).filter(curImage);
		updateImage();
		dialog->close();
	});
	dialog->show();	
}

void MainWindow::fileCreateNewImageSlot() {
	if (!curImage.isNull()) {
		QMessageBox::StandardButton reply = QMessageBox::question(this, "Test", "Delete current image?", QMessageBox::Yes | QMessageBox::No);
		if (reply == QMessageBox::No) {
			return;
		}
	}
	QDialog* parametersOfNewImage = new QDialog(this);
	
	QWidget* widgetForDialog = new QWidget(parametersOfNewImage);
	QVBoxLayout* vlayoutForDialog = new QVBoxLayout(widgetForDialog);

	QHBoxLayout* widthLayout = new QHBoxLayout(widgetForDialog);
	vlayoutForDialog->addLayout(widthLayout);
	QLabel* widthLabel = new QLabel("Width: ", widgetForDialog);
	widthLayout->addWidget(widthLabel);
	QSpinBox* widthData = new QSpinBox(widgetForDialog);
	widthData->setRange(0, 7680);
	widthLayout->addWidget(widthData);

	QHBoxLayout* heightLayout = new QHBoxLayout(widgetForDialog);
	vlayoutForDialog->addLayout(heightLayout);
	QLabel* heightLabel = new QLabel("Height: ", widgetForDialog);
	heightLayout->addWidget(heightLabel);
	QSpinBox* heightData = new QSpinBox(widgetForDialog);
	heightData->setRange(0, 4320);
	heightLayout->addWidget(heightData);

	QPushButton* chooseColorButton = new QPushButton("Choose background color", widgetForDialog);
	vlayoutForDialog->addWidget(chooseColorButton);
	QColor* backgroundColor = new QColor(255, 255, 255); //white
	connect(chooseColorButton, &QPushButton::clicked, [backgroundColor]() {
		*backgroundColor = QColorDialog::getColor();
	});
	QPushButton* applyButton = new QPushButton("Create", widgetForDialog);
	vlayoutForDialog->addWidget(applyButton);
	connect(applyButton, &QPushButton::clicked, [widthData, heightData, backgroundColor, this, parametersOfNewImage]() {
		curImage = QImage(widthData->value(), heightData->value(), QImage::Format_ARGB32);
		curImage.fill(*backgroundColor);
		delete backgroundColor;
		updateImage();
		parametersOfNewImage->close();
	});
	parametersOfNewImage->setFixedSize(widgetForDialog->sizeHint());
	parametersOfNewImage->show();
}
