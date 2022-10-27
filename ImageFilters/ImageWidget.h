#pragma once
#include <QtWidgets>
#include <iostream>
#include <optional>

#include "PaintManager.h"
#include "ProgramState.h"

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageWidget(QWidget* parent = 0);
    QImage& getImage();
    void setImage(const QImage& image);

    PaintManager& getPaintManager() { return pm; }


public slots:
    void setPixmap(const QImage& image);
    void changedMode();

protected:
    void paintEvent(QPaintEvent* event);

    void mousePressEvent(QMouseEvent* e) override;

    void mouseReleaseEvent(QMouseEvent* e) override;

    void mouseMoveEvent(QMouseEvent* e) override;


private:
    QImage image;
    QPoint posImage;
    QSize displayPixSize;

    std::optional<QPointF> lastPressedPoint;
    
    bool mousePressed = false;
    PaintManager pm;
};
