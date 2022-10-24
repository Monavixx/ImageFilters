#include "ImageWidget.h"

ImageWidget::ImageWidget(QWidget* parent) :
    QWidget(parent)
{
    pm.setColor(QColor(255, 0, 0));
    pm.setWidth(20);
    connect(ProgramState::getInstance(), &ProgramState::changedMode, this, &ImageWidget::changedMode);
}
QImage& ImageWidget::getImage() {
    return image;
}
void ImageWidget::setImage(const QImage& image) {
    this->image = image;
}

void ImageWidget::setPixmap(const QImage& image) {
    this->image = image;
    repaint();
}

void ImageWidget::changedMode() {
    switch (ProgramState::getMode()) {
    case InstrumentEnum::PAINT: {
        this->setCursor(Qt::CrossCursor);
        break;
    }
    case InstrumentEnum::DEFAULT: {
        this->setCursor(Qt::ArrowCursor);
        break;
    }
    }
}

void ImageWidget::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    if (image.isNull())
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    displayPixSize = image.size();
    displayPixSize.scale(event->rect().size(), Qt::KeepAspectRatio);

    QPixmap scaledPix = QPixmap::fromImage(image).scaled(displayPixSize,
        Qt::KeepAspectRatio,
        Qt::SmoothTransformation
    );

    posImage.setX((event->rect().size().width() - scaledPix.width()) / 2);
    posImage.setY((event->rect().size().height() - scaledPix.height()) / 2);
    painter.drawPixmap(posImage, scaledPix);
}


void ImageWidget::mousePressEvent(QMouseEvent* e) {
    mousePressed = true;
    double x = (e->localPos().x() - posImage.x()) / ((double)displayPixSize.width() / (double)image.width());
    double y = (e->localPos().y() - posImage.y()) / ((double)displayPixSize.height() / (double)image.height());
    lastPressedPoint.emplace(x, y);
    if (ProgramState::getMode() == InstrumentEnum::PAINT) {
        pm.draw_point(image, *lastPressedPoint);
        repaint();
    }
}
void ImageWidget::mouseReleaseEvent(QMouseEvent* e) {
    mousePressed = false;
    lastPressedPoint.reset();
}

void ImageWidget::mouseMoveEvent(QMouseEvent* e) {
    if (ProgramState::getMode() == InstrumentEnum::PAINT && mousePressed) {
        double x = (e->localPos().x() - posImage.x()) / ((double)displayPixSize.width() / (double)image.width());
        double y = (e->localPos().y() - posImage.y()) / ((double)displayPixSize.height() / (double)image.height());

        if (lastPressedPoint.has_value()) {
            pm.draw_line(image, { x, y }, *lastPressedPoint);
        }
        repaint();

        lastPressedPoint.emplace(x, y);
    }
}