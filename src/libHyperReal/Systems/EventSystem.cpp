#include <HyperReal/Systems/EventSystem.h>
#include <HyperReal/libHyperReal.h>

EventSystem::EventSystem(libHyperReal* hyperReal, HyperRealWindow* window)
	: ISystem(hyperReal, window)
{
}

EventSystem::~EventSystem()
{
}

void EventSystem::Initialize()
{

}

void EventSystem::Terminate()
{

}

void EventSystem::Update(ui32 frameNo, f32 timeDelta)
{
	//if (glfwGetKey(window, GLFW_KEY_ESC) == GLFW_PRESS) {

	//}
}
