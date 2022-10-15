#pragma once

#include "IFilter.h"
#include <vector>

class FilterList {
private:
	std::vector<IFilter*> filters;

public:
	FilterList(std::initializer_list<IFilter*> filters) : filters(filters) {}
	~FilterList() {
		for (auto filter : filters) {
			delete filter;
		}
	}
	QImage apply(QImage image) {
		for (auto filter : filters) {
			image = filter->filter(image);
		}
	}
};
