#pragma once

#include "IFilter.h"
#include <vector>

class FilterList {
private:
	std::vector<IFilter*> filters;

public:
	FilterList(std::initializer_list<IFilter*> filters);
	~FilterList();
	QImage apply(QImage image);
};
