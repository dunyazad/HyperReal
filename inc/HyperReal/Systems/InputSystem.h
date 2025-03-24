#pragma once

#include <HyperReal/HyperRealCommon.h>

class InputSystem : public ISystem
{
public:
	InputSystem(libHyperReal* hyperReal, HyperRealWindow* window);
	virtual ~InputSystem();

	virtual void Initialize();
	virtual void Terminate();

	virtual void Update(ui32 frameNo, f32 timeDelta);

	bool IsKeyDown(int key) const;
	bool IsMouseDown(int button) const;
	float GetScrollOffset() const;

private:
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

	inline static std::unordered_map<int, bool> keyStates;
	inline static std::unordered_map<int, bool> mouseButtonStates;
	inline static float mousePositionX = 0.0f;
	inline static float mousePositionY = 0.0f;
	inline static float scrollOffsetY = 0.0f;
};
