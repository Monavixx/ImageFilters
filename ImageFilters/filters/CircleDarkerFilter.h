#pragma once
#include "IFilter.h"

class SecondFilter : public IFilter {
private:
	const int radius;
public:
	SecondFilter(const int radius = 100) : radius(radius) {}

	QImage filter(const QImage& image) const override {
		QImage newImage(image.width(), image.height(), image.format());// = image;

		QPoint center{ newImage.width() / 2 , newImage.height() / 2};
		int leftX = center.x() - radius;
		int rightX = center.x() + radius;
		int upY = center.y() - radius;
		int downY = center.y() + radius;

		for (int j = 0; j <= image.height(); ++j) {
			for (int i = 0; i <= image.width(); ++i) {
				if ((pow(i - center.x(), 2) + pow(j - center.y(), 2)) <= pow(radius, 2)) {
					int dark = sqrt(pow(center.x() - i, 2) + pow(center.y() - j, 2)) / radius * 255;
					QColor color = image.pixelColor(i, j);
					int r = color.red() - dark, g = color.green() - dark, b = color.blue() - dark;
					r = r >= 0 ? r : 0;
					g = g >= 0 ? g : 0;
					b = b >= 0 ? b : 0;
					newImage.setPixelColor(i, j, QColor(r, g, b));
				}
				else {
					newImage.setPixelColor(i, j, image.pixelColor(i,j));
				}
			}
		}

		return newImage;
	}
};
