#pragma once
#include <QtWidgets>
#include <iostream>

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget* parent = 0) :
        QWidget(parent), mode(Mode::DEFAULT) {}
    QImage& getImage() {
        return image;
    }
    void setImage(const QImage& image) {
        this->image = image;
    }

    enum class Mode {
        DEFAULT,
        PAINT
    };


public slots:
    void setPixmap(const QImage& image) {
        this->image = image;
        repaint();
    }

    void paintModeChange() {
        if (mode != Mode::PAINT) {
            this->setCursor(Qt::CrossCursor);
            mode = Mode::PAINT;
        }
        else {
            defaultModeActivate();
        }
    }
    void defaultModeActivate() {
        mode = Mode::DEFAULT;
        this->setCursor(Qt::ArrowCursor);
    }

protected:
    void paintEvent(QPaintEvent* event) {
        QWidget::paintEvent(event);

        if (image.isNull())
            return;

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QSize pixSize = image.size();
        pixSize.scale(event->rect().size(), Qt::KeepAspectRatio);

        QPixmap scaledPix = QPixmap::fromImage(image).scaled(pixSize,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        );

        posImage.setX((event->rect().size().width() - scaledPix.width()) / 2);
        posImage.setY((event->rect().size().height() - scaledPix.height()) / 2);
        painter.drawPixmap(posImage, scaledPix);

    }


    void mousePressEvent(QMouseEvent* e) override {
        mousePressed = true;
    }
    void mouseReleaseEvent(QMouseEvent* e) override {
        mousePressed = false;
    }

    void mouseMoveEvent(QMouseEvent* e) override {
        if (mode == Mode::PAINT && mousePressed) {
            int x = (e->localPos().x() - posImage.x()) / 2;
            int y = (e->localPos().y() - posImage.y()) / 2;
            image.setPixelColor(x + 1, y, QColor(0, 0, 0));
            image.setPixelColor(x, y + 1, QColor(0, 0, 0));
            image.setPixelColor(x - 1, y, QColor(0, 0, 0));
            image.setPixelColor(x, y - 1, QColor(0, 0, 0));
            image.setPixelColor(x, y, QColor(0, 0, 0));
            repaint();
        }
    }


private:
    QImage image;
    QPoint posImage;
    Mode mode;
    
    bool mousePressed = false;
};
