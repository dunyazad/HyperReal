#pragma once

#include<HyperReal/HyperRealCommon.h>

class HyperRealWindow
{
public:
	HyperRealWindow();
	~HyperRealWindow();

	GLFWwindow* Initialize(ui32 width, ui32 height);
	void Terminate();

	inline GLFWwindow* GetGLFWwindow() const { return window; }
	inline ui32 GetWidth() const { return width; }
	inline ui32 GetHeight() const { return height; }

	static void FrameBufferSizeCallback(GLFWwindow* window, i32 width, i32 height);

private:
	static HyperRealWindow* s_instance;

	GLFWwindow* window = nullptr;
	ui32 width = 1920;
	ui32 height = 1024;
};
