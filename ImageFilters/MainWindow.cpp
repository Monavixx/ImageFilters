#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), showedImage(nullptr), panelOfInstruments(nullptr)
{
}

void MainWindow::init() {
	showedImage = new ImageWidget(this);
	setCentralWidget(showedImage);

	QMenu* fileMenu = menuBar()->addMenu("File");
	QAction* fileOpenImageAction = fileMenu->addAction("Open image", QKeySequence::Open);
	connect(fileOpenImageAction, &QAction::triggered, this, &MainWindow::fileOpenImageSlot);
	QAction* fileSaveImageAction = fileMenu->addAction("Save image", QKeySequence::Save);
	connect(fileSaveImageAction, &QAction::triggered, this, &MainWindow::fileSaveImageSlot);
	QAction* fileCreateNewImageAction = fileMenu->addAction("Create new image", QKeySequence::New);
	connect(fileCreateNewImageAction, &QAction::triggered, this, &MainWindow::fileCreateNewImageSlot);

	fileMenu->addSeparator();
	QAction* fileQuitAction = fileMenu->addAction("Quit", QKeySequence::Quit);
	connect(fileQuitAction, &QAction::triggered, this, &MainWindow::close);

	QMenu* filtersMenu = menuBar()->addMenu("Filters");
	QAction* filterNegativeAction = filtersMenu->addAction("Negative");
	connect(filterNegativeAction, &QAction::triggered, this, &MainWindow::filtersNegativeSlot);
	QAction* filterSecondAction = filtersMenu->addAction("Circle darker");
	connect(filterSecondAction, &QAction::triggered, this, &MainWindow::filtersCirleDarkerSlot);

	panelOfInstruments = new PanelOfInstruments(this);
	auto dwpanelOfInstruments = new QDockWidget("Instruments", this);
	dwpanelOfInstruments->setWidget(panelOfInstruments);
	dwpanelOfInstruments->setFeatures(QDockWidget::DockWidgetMovable);
	this->addDockWidget(Qt::LeftDockWidgetArea, dwpanelOfInstruments, Qt::Vertical);

	panelOfParametersOfCurrentInstrument = new PanelOfParametersOfCurrentInstrument(this);
	auto dwPanelOfParametersOfCurrentInstrument = new QDockWidget("Parameters", this);
	dwPanelOfParametersOfCurrentInstrument->setWidget(panelOfParametersOfCurrentInstrument);
	dwPanelOfParametersOfCurrentInstrument->setFeatures(QDockWidget::DockWidgetMovable);
	this->setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
	this->setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
	this->setCorner(Qt::BottomRightCorner, Qt::NoDockWidgetArea);
	this->addDockWidget(Qt::RightDockWidgetArea, dwPanelOfParametersOfCurrentInstrument, Qt::Horizontal);
	
}

MainWindow::~MainWindow()
{}

void MainWindow::updateImage()
{
	showedImage->repaint();
}
void MainWindow::updateImage(const QImage& image) {
	setCurImage(image);
	updateImage();
}

void MainWindow::fileOpenImageSlot() {
	QString filename{ QFileDialog::getOpenFileName(this, "Open image", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation), "*.png")};
	curImage().load(filename);

	updateImage();
}

void MainWindow::fileSaveImageSlot() {
	curImage().save(QFileDialog::getSaveFileName(this, "Save image", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation), "*.png"));
}

void MainWindow::filtersNegativeSlot() {
	setCurImage(NegativeFilter().filter(curImage()));
	updateImage();
}

void MainWindow::filtersCirleDarkerSlot() {
	CircleDarkerDialog* dialog = new CircleDarkerDialog(this);
	dialog->show();
}

void MainWindow::fileCreateNewImageSlot() {
	if (!curImage().isNull()) {
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
		setCurImage(QImage(widthData->value(), heightData->value(), QImage::Format_ARGB32));
		curImage().fill(*backgroundColor);
		delete backgroundColor;
		updateImage();
		parametersOfNewImage->close();
	});
	parametersOfNewImage->setFixedSize(widgetForDialog->sizeHint());
	parametersOfNewImage->show();
}

