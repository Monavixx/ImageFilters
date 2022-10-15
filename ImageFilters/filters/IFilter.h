#pragma once

#include <QtWidgets>

class IFilter {
public:
	virtual QImage filter(const QImage& image) const = 0;
};
