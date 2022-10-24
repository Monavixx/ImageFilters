#pragma once
#include "IFilter.h"

class NegativeFilter : public IFilter {
public:
	QImage filter(const QImage& image) const override;
};
