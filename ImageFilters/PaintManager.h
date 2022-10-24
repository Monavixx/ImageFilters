#pragma once

#include <QtWidgets>

#include "readAll.h"

class PaintManager {
public:
	PaintManager();
	~PaintManager();

	const QColor& getColor() const { return pen.color(); }
	int getWidth() const { return pen.width(); }

	void setColor(const QColor& color) { pen.setColor(color); }
	void setWidth(int width) { pen.setWidth(width); }

	void draw_line(QImage& image, QPointF from, QPointF to);
	void draw_point(QImage& image, QPointF point);
private:
	QPen pen;
};
