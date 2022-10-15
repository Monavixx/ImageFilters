#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	//menu
	QMenu* fileMenu = menuBar()->addMenu("File");
	QAction* fileOpenImageAction = fileMenu->addAction("Open image", QKeySequence::Open);
	connect(fileOpenImageAction, &QAction::triggered, this, &MainWindow::fileOpenImageSlot);
	QAction* fileSaveImageAction = fileMenu->addAction("Save image", QKeySequence::Save);
	connect(fileSaveImageAction, &QAction::triggered, this, &MainWindow::fileSaveImageSlot);

	QMenu* filtersMenu = menuBar()->addMenu("Filters");
	QAction* filterNegativeAction = filtersMenu->addAction("Negative");
	connect(filterNegativeAction, &QAction::triggered, this, &MainWindow::filtersNegativeSlot);
	QAction* filterSecondAction = filtersMenu->addAction("Second");
	connect(filterSecondAction, &QAction::triggered, this, &MainWindow::filtersSecondSlot);

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
	QFileDialog fd(this);
	QString filename{ fd.getOpenFileName() };
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

void MainWindow::filtersSecondSlot() {
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
		updateImage(SecondFilter(value).filter(curImage));
	});
	connect(pbExit, &QPushButton::clicked, [dialog, slider, this]() {
		curImage = SecondFilter(slider->value()).filter(curImage);
		updateImage();
		dialog->close();
	});
	dialog->show();	
}