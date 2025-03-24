#pragma once

#include <HyperReal/HyperRealCommon.h>

struct Transform
{
	Eigen::Matrix4f absoluteTransform;
	Eigen::Matrix4f transform;
	Transform* parent = nullptr;
	vector<Transform*> children;
};
