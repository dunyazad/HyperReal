#pragma once

#include <HyperReal/HyperRealCommon.h>

class ImmediateRenderSystem : public ISystem
{
public:
	ImmediateRenderSystem(libHyperReal* hyperReal, HyperRealWindow* window);
	virtual ~ImmediateRenderSystem();

	virtual void Initialize();
	virtual void Terminate();

	virtual void Update(ui32 frameNo, f32 timeDelta);
};