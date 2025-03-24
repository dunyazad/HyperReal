#pragma once

#include <HyperReal/HyperRealCommon.h>

struct Camera
{
	Eigen::Matrix4f viewMatrix;
	Eigen::Matrix4f projectionMatrix;
};
