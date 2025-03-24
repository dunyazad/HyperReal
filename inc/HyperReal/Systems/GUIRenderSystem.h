#pragma once

#include <HyperReal/HyperRealCommon.h>

class GUIRenderSystem : public ISystem
{
public:
	GUIRenderSystem(libHyperReal* hyperReal, HyperRealWindow* window);
	virtual ~GUIRenderSystem();

	void ReloadFont(float newFontSize);

	virtual void Initialize() override;
	virtual void Terminate() override;

	virtual void Update(ui32 frameNo, f32 timeDelta);

	void ShowFPS();
	void ShowUIPanel();
	void ShowGraphPanel();
	void ShowStatus();

	f32 fontSize = 18.0f;

	const ui32 historySize = 50;

	vector<f32> fpsHistory;
	ui32 historyOffset = 0;
	f32 accumulatedFPS = 0.0f;
	ui32 frameCount = 0;
	const ui32 updateRate = 10;
	bool vSync = true;

	ui32 mouseX = 0;
	ui32 mouseY = 0;

	bool needFontReload = true;
};
