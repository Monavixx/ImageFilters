#pragma once
#include <QtWidgets>
#include <iostream>
#include <optional>

#include "PaintManager.h"

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget* parent = 0) :
        QWidget(parent), mode(Mode::DEFAULT) 
    {
        pm.setColor(QColor(255, 0, 0));
        pm.setWidth(20);
    }
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


    void mousePressEvent(QMouseEvent* e) override {
        mousePressed = true;
        double x = (e->localPos().x() - posImage.x()) / ((double)displayPixSize.width() / (double)image.width());
        double y = (e->localPos().y() - posImage.y()) / ((double)displayPixSize.height() / (double)image.height());
        lastPressedPoint.emplace(x, y);
    }
    void mouseReleaseEvent(QMouseEvent* e) override {
        mousePressed = false;
        lastPressedPoint.reset();
    }

    void mouseMoveEvent(QMouseEvent* e) override {
        if (mode == Mode::PAINT && mousePressed) {
            double x = (e->localPos().x() - posImage.x()) / ((double)displayPixSize.width() / (double)image.width());
            double y = (e->localPos().y() - posImage.y()) / ((double)displayPixSize.height() / (double)image.height());

            if (lastPressedPoint.has_value()) {
                pm.draw_line(image, { x, y }, *lastPressedPoint);
            }
            repaint();

            lastPressedPoint.emplace(x, y);
        }
    }


private:
    QImage image;
    QPoint posImage;
    QSize displayPixSize;
    Mode mode;

    std::optional<QPointF> lastPressedPoint;
    
    bool mousePressed = false;
    PaintManager pm;
};
