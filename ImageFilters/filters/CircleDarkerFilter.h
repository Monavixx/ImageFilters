#pragma once
#include "IFilter.h"

#ifdef MAC
#include <CL/OpenCL.hpp>
#else
#include <CL/cl.hpp>
#endif

#include "../readAll.h"


class CircleDarkerFilter : public IFilter {
private:
	const int radius;


	inline static const std::string sourceStr = read_all(R"(D:\Projects\C++\ImageFilters\ImageFilters\circleDarker.cl)");
	inline static cl::Program::Sources source;
	inline static cl::Program program;
	inline static auto device = cl::Device::getDefault();
	inline static auto context = cl::Context(device);
	inline static cl::Kernel kernel;
	inline static cl::CommandQueue commandQueue;
public:
	CircleDarkerFilter(const int radius = 100);

	static void init();

	QImage filter(const QImage& image) const override;
};
