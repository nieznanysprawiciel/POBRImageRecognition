#ifndef HELPERS_CPP
#define HELPERS_CPP

#include "Helpers.h"


cv::Vec3b Clamp( cv::Vec3f vector )
{
	cv::Vec3b result;
	for (int i = 0; i < 3; ++i)
	{
		vector[i] = vector[i] > 255 ? 255 : vector[i];
		vector[i] = vector[i] < 0 ? 0 : vector[i];
	}
	result = vector;
	return result;
}

void FillMatrix( cv::Mat1f& matrix,
	float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3,
	float divider )
{
	matrix(0, 0) = x1 / divider;
	matrix(0, 1) = y1 / divider;
	matrix(0, 2) = z1 / divider;

	matrix(1, 0) = x2 / divider;
	matrix(1, 1) = y2 / divider;
	matrix(1, 2) = z2 / divider;

	matrix(2, 0) = x3 / divider;
	matrix(2, 1) = y3 / divider;
	matrix(2, 2) = z3 / divider;
}

#endif // HELPERS_CPP
