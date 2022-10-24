#include "FilterList.h"

FilterList::FilterList(std::initializer_list<IFilter*> filters) : filters(filters) {}

FilterList::~FilterList() {
	for (auto filter : filters) {
		delete filter;
	}
}
QImage FilterList::apply(QImage image) {
	for (auto filter : filters) {
		image = filter->filter(image);
	}
	return image;
}