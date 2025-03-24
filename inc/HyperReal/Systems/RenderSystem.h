#pragma once

#include <HyperReal/HyperRealCommon.h>

class RenderSystem : public ISystem
{
public:
	RenderSystem(libHyperReal* hyperReal, HyperRealWindow* window);
	virtual ~RenderSystem();

	virtual void Initialize();
	virtual void Terminate();

	virtual void Update(ui32 frameNo, f32 timeDelta);
};
