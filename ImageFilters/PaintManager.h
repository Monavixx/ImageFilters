#pragma once

#include <QtWidgets>

#ifdef MAC
#include <CL/OpenCL.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "readAll.h"

class PaintManager {
public:
	PaintManager();
	~PaintManager();

	const QColor& getColor() const { return color; }
	int getWidth() const { return width; }

	void setColor(const QColor& color) { this->color = color; }
	void setColor(QColor&& color) { this->color = std::move(color); }
	void setWidth(int width) { this->width = width; }

	void draw_line(QImage& image, QPointF from, QPointF to);
private:
	QColor color;
	int width;
};
