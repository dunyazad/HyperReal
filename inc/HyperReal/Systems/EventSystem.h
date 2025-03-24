#pragma once

#include <HyperReal/HyperRealCommon.h>

class EventSystem : public ISystem
{
public:
	EventSystem(libHyperReal* hyperReal, HyperRealWindow* window);
	virtual ~EventSystem();

	virtual void Initialize();
	virtual void Terminate();

	virtual void Update(ui32 frameNo, f32 timeDelta);
};
