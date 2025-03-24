#pragma once

#include <HyperReal/HyperRealCommon.h>

class TransformSystem : public ISystem
{
public:
	TransformSystem(libHyperReal* hyperReal, HyperRealWindow* window);
	virtual ~TransformSystem();

	virtual void Initialize();
	virtual void Terminate();

	virtual void Update(ui32 frameNo, f32 timeDelta);
};
