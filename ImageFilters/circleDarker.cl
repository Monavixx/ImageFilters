__constant sampler_t sampler = CLK_NORMALIZED_COORDS_TRUE | CLK_ADDRESS_NONE | CLK_FILTER_NEAREST;

__kernel void circleDarker(read_only image2d_t image, write_only image2d_t outputImage, int centerX, int centerY, int radius)
{
	int j = get_global_id(0);
	int i = get_global_id(1);

	uint dist = sqrt(pow((double)(i - centerX), 2) + pow((double)(j - centerY), 2));
	uint4 pixelColor = read_imageui(image, sampler, (int2)(i, j));
	if (dist <= radius) {
		/*
			dark is number from 0 to 255
		*/
		uint dark = (double)dist / (double)radius * 255;

		int r = pixelColor.x - dark, g = pixelColor.y - dark, b = pixelColor.z - dark;
		r = r >= 0 ? r : 0;
		g = g >= 0 ? g : 0;
		b = b >= 0 ? b : 0;

		write_imageui(outputImage, (int2)(i, j), (uint4)(r, g, b, 255));
	}
	else {
		write_imageui(outputImage, (int2)(i, j), pixelColor);
	}
}