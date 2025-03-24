#include <HyperReal/Systems/InputSystem.h>
#include <HyperReal/HyperRealWindow.h>

InputSystem::InputSystem(libHyperReal* hyperReal, HyperRealWindow* window)
	: ISystem(hyperReal, window)
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::Initialize()
{
	GLFWwindow* nativeWindow = window->GetGLFWwindow();

	glfwSetKeyCallback(nativeWindow, KeyCallback);
	glfwSetMouseButtonCallback(nativeWindow, MouseButtonCallback);
    glfwSetCursorPosCallback(nativeWindow, MousePositionCallback);
	glfwSetScrollCallback(nativeWindow, ScrollCallback);
}

void InputSystem::Terminate()
{
	keyStates.clear();
	mouseButtonStates.clear();
	scrollOffsetY = 0.0f;
}

void InputSystem::Update(ui32 frameNo, f32 timeDelta)
{
	// Clear scroll after reading
	scrollOffsetY = 0.0f;

	// Optional: handle key events here per frame if needed
}

bool InputSystem::IsKeyDown(int key) const
{
    auto it = keyStates.find(key);
    return it != keyStates.end() && it->second;
}

bool InputSystem::IsMouseDown(int button) const
{
    auto it = mouseButtonStates.find(button);
    return it != mouseButtonStates.end() && it->second;
}

float InputSystem::GetScrollOffset() const
{
    return scrollOffsetY;
}

void InputSystem::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
        keyStates[key] = true;
    else if (action == GLFW_RELEASE)
        keyStates[key] = false;

    hrlog("key : %d, scancode : %d, action : %d, mods : %d\n", key, scancode, action, mods);
}

void InputSystem::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
        mouseButtonStates[button] = true;
    else if (action == GLFW_RELEASE)
        mouseButtonStates[button] = false;

    hrlog("button : %d, action : %d, mods : %d\n", button, action, mods);
}

void InputSystem::MousePositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    mousePositionX = static_cast<float>(xpos);
    mousePositionY = static_cast<float>(ypos);

    hrlog("xpos : %f, ypos : %f\n", xpos, ypos);
}

void InputSystem::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    scrollOffsetY = static_cast<float>(yoffset);

    hrlog("xoffset : %f, yoffset : %f\n", xoffset, yoffset);
}
