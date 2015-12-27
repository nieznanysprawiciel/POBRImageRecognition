#ifndef HELPERS_H
#define HELPERS_H

#include "opencv2/core/core.hpp"

cv::Vec3b Clamp( cv::Vec3f vector );

void FillMatrix( cv::Mat1f& matrix,
	float x1, float y1, float z1,
	float x2, float y2, float z2,
	float x3, float y3, float z3,
	float divider );

#endif // HELPERS_H
