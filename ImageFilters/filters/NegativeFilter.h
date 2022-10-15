#pragma once
#include "IFilter.h"

class NegativeFilter : public IFilter {
public:
	QImage filter(const QImage& image) const override {
		QImage newImage(image.width(), image.height(), image.format());
		for (size_t i = 0; i < newImage.width(); ++i) {
			for (size_t j = 0; j < newImage.height(); ++j) {
				QColor color = image.pixelColor(i, j);
				color.setBlue(255 - color.blue());
				color.setRed(255 - color.red());
				color.setGreen(255 - color.green());
				newImage.setPixelColor(i, j, color);
			}
		}
		return newImage;
	}
};
