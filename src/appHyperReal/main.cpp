#include <iostream>

#include <HyperReal/libHyperReal.h>
auto& HR = HyperReal;

int main(int argc, char** argv)
{
	HR.Initialize(1920, 1080);

	auto appMain = HR.CreateEntity();

	auto camera = HR.CreateEntity();
	auto& transform = HR.CreateComponent<Transform>(camera);

	HR.RegisterEvent<KeyEvent>(appMain, [&](Entity entity, KeyEvent&& event) {
			hrlog("Entity : %d, key : %d, scancode : %d, action : %d, mods : %d\n",
				entity, event.key, event.scancode, event.action, event.mods);
			if (GLFW_KEY_ESCAPE == event.key)
			{
				glfwSetWindowShouldClose(HR.GetHyperRealWindow()->GetGLFWwindow(), true);
			}
		});

	HR.Run();

	HR.Terminate();

	return 0;
}
