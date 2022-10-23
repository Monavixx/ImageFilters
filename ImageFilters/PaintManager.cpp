#include "PaintManager.h"

PaintManager::PaintManager() : width(1), color(0,0,0) {

}

PaintManager::~PaintManager() {

}


void PaintManager::draw_line(QImage& image, QPointF from, QPointF to) {
    QPixmap pxm = QPixmap::fromImage(image);
    QPainter p(&pxm);
    p.setPen(QPen(QBrush(color), width));
    p.setRenderHint(QPainter::RenderHint::Antialiasing);
    p.drawLine(from, to);
    image = pxm.toImage();
}

