#include "PaintManager.h"

PaintManager::PaintManager() : pen(QBrush(Qt::black), 1) {

}

PaintManager::~PaintManager() {

}


void PaintManager::draw_line(QImage& image, QPointF from, QPointF to) {
    QPixmap pxm = QPixmap::fromImage(image);
    QPainter p(&pxm);
    p.setPen(pen);
    p.setRenderHint(QPainter::RenderHint::Antialiasing);
    p.drawLine(from, to);
    image = pxm.toImage();
}

void PaintManager::draw_point(QImage& image, QPointF point)
{
    QPixmap pxm = QPixmap::fromImage(image);
    QPainter p(&pxm);
    p.setPen(pen);
    p.setRenderHint(QPainter::RenderHint::Antialiasing);
    p.drawPoint(point);
    image = pxm.toImage();
}

