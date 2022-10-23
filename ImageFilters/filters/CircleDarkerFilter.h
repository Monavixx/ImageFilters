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
	CircleDarkerFilter(const int radius = 100) : radius(radius) {}

	static void init() {
		source.push_back({ sourceStr.c_str(), source.size() });
		program = cl::Program(context, source);
		program.build();
		//auto str = program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device); //DEBUG
		//std::cout << str;

		kernel = cl::Kernel(program, "circleDarker");
		commandQueue = cl::CommandQueue(context, device);
	}

	QImage filter(const QImage& image) const override {
		QImage newImage = image;//(image.width(), image.height(), image.format());

		QPoint center{ newImage.width() / 2 , newImage.height() / 2 };
		int leftX = center.x() - radius;
		int rightX = center.x() + radius;
		int upY = center.y() - radius;
		int downY = center.y() + radius;

		cl::ImageFormat imageFormat(CL_RGBA, CL_UNSIGNED_INT8);
		cl::Image2D inputImage(context, CL_MEM_READ_ONLY, imageFormat, image.width(), image.height());
		cl::Image2D outputImage(context, CL_MEM_WRITE_ONLY, imageFormat, image.width(), image.height());

		cl::size_t<3> origin;
		cl::size_t<3> region;
		region[0] = image.width(); region[1] = image.height(); region[2] = 1;

		commandQueue.enqueueWriteImage(inputImage, CL_TRUE, origin, region, image.bytesPerLine(), 0, newImage.bits(), 0);

		kernel.setArg(0, inputImage);
		kernel.setArg(1, outputImage);
		kernel.setArg(2, center.x());
		kernel.setArg(3, center.y());
		kernel.setArg(4, radius);

		commandQueue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(image.height(), image.width()), cl::NullRange, NULL);
		commandQueue.enqueueReadImage(outputImage, CL_TRUE, origin, region, image.bytesPerLine(), 0, newImage.bits());

		commandQueue.finish();


		return newImage;
	}
};
