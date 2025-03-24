#pragma once

#include <HyperReal/HyperRealCommon.h>

class CameraSystem : public ISystem
{
public:
	CameraSystem(libHyperReal* hyperReal, HyperRealWindow* window);
	virtual ~CameraSystem();

	virtual void Initialize();
	virtual void Terminate();

	virtual void Update(ui32 frameNo, f32 timeDelta);
};
